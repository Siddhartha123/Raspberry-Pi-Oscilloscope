/**
 * Convenience classes that package different levels
 * of functionality of Circle applications.
 *
 * Derive the kernel class of the application from one of
 * the CStdlibApp* classes and implement at least the
 * Run () method. Extend the Initalize () and Cleanup ()
 * methods if necessary.
 */
#ifndef _circle_stdlib_app_h
#define _circle_stdlib_app_h

#define SPI_CLOCK_SPEED 2000000 // Hz
#define SPI_CPOL 0
#define SPI_CPHA 0

#include <circle/actled.h>
#include <circle/koptions.h>
#include <circle/devicenameservice.h>
#include <circle/nulldevice.h>
#include <circle/exceptionhandler.h>
#include <circle/interrupt.h>
#include <circle/screen.h>
#include <circle/serial.h>
#include <circle/timer.h>
#include <circle/logger.h>
#include <circle/usb/usbhcidevice.h>
#include <SDCard/emmc.h>
#include <circle/fs/fat/fatfs.h>
#include <circle/input/console.h>
#include <circle/sched/scheduler.h>
#include <circle/net/netsubsystem.h>
#include <circle/spimaster.h>
#include <littlevgl/littlevgl.h>
#include <circle_glue.h>

/**
 * Basic Circle Stdlib application that supports GPIO access.
 */
class CStdlibApp
{
public:
        enum TShutdownMode
        {
                ShutdownNone,
                ShutdownHalt,
                ShutdownReboot
        };

        CStdlibApp (const char *kernel) :
                FromKernel (kernel)
        {
        }

        virtual ~CStdlibApp (void)
        {
        }

        virtual bool Initialize (void)
        {
                return mInterrupt.Initialize ();
        }

        virtual void Cleanup (void)
        {
        }

        virtual TShutdownMode Run (void) = 0;

        const char *GetKernelName(void) const
        {
                return FromKernel;
        }

protected:
        CActLED            mActLED;
        CKernelOptions     mOptions;
        CDeviceNameService mDeviceNameService;
        CNullDevice        mNullDevice;
        CExceptionHandler  mExceptionHandler;
        CInterruptSystem   mInterrupt;

private:
        char const *FromKernel;
};

/**
 * Stdlib application that adds screen support
 * to the basic CStdlibApp features.
 */
class CStdlibAppScreen : public CStdlibApp
{
public:
        CStdlibAppScreen(const char *kernel)
                : CStdlibApp (kernel),
                  mScreen (mOptions.GetWidth (), mOptions.GetHeight ()),
                  mTimer (&mInterrupt),
                  mLogger (mOptions.GetLogLevel (), &mTimer),
		  mGUI (&mScreen, &mInterrupt)
        {
        }

	
        virtual bool Initialize (void)
        {
                if (!CStdlibApp::Initialize ())
                {
                        return false;
                }

                if (!mScreen.Initialize ())
                {
                        return false;
                }

                if (!mSerial.Initialize (115200))
                {
                        return false;
                }

                CDevice *pTarget =
                        mDeviceNameService.GetDevice (mOptions.GetLogDevice (), false);
                if (pTarget == 0)
                {
                        pTarget = &mScreen;
                }

                if (!mLogger.Initialize (pTarget))
                {
                        return false;
                }

		if (!mTimer.Initialize ())
                {
                        return false;
                }		

                return mGUI.Initialize ();
        }

protected:
        CScreenDevice   mScreen;
        CSerialDevice   mSerial;
        CTimer          mTimer;
        CLogger         mLogger;
	CLittlevGL	mGUI;
	
};

/**
 * Stdlib application that adds stdio support
 * to the CStdlibAppScreen functionality.
 */
class CStdlibAppStdio: public CStdlibAppScreen
{
private:
        char const *mpPartitionName;

public:
        // T�DO transform to constexpr
        // constexpr char static DefaultPartition[] = "emmc1-1";
#define CSTDLIBAPP_DEFAULT_PARTITION "emmc1-1"

        CStdlibAppStdio (const char *kernel,
                         const char *pPartitionName = CSTDLIBAPP_DEFAULT_PARTITION)
                : CStdlibAppScreen (kernel),
                  mpPartitionName (pPartitionName),
                  mUSBHCI (&mInterrupt, &mTimer),
                  mEMMC (&mInterrupt, &mTimer, &mActLED),
                  mConsole (&mScreen),
		  mSPIMaster(SPI_CLOCK_SPEED, SPI_CPOL, SPI_CPHA)

        {
        }

        virtual bool Initialize (void)
        {
                if (!CStdlibAppScreen::Initialize ())
                {
                        return false;
                }

                if (!mEMMC.Initialize ())
                {
                        return false;
                }

                CDevice * const pPartition =
                        mDeviceNameService.GetDevice (mpPartitionName, true);
                if (pPartition == 0)
                {
                        mLogger.Write (GetKernelName (), LogError,
                                       "Partition not found: %s", mpPartitionName);

                        return false;
                }

                if (!mFileSystem.Mount (pPartition))
                {
                        mLogger.Write (GetKernelName (), LogError,
                                         "Cannot mount partition: %s", mpPartitionName);

                        return false;
                }

                if (!mUSBHCI.Initialize ())
                {
                        return false;
                }

                if (!mConsole.Initialize ())
                {
                        return false;
                }
		
		if (!mSPIMaster.Initialize ())
                {
                        return false;
                }

                // Initialize newlib stdio with a reference to Circle's file system and console
                CGlueStdioInit (mFileSystem, mConsole);

                mLogger.Write (GetKernelName (), LogNotice, "Compile time: " __DATE__ " " __TIME__);

                return true;
        }

        virtual void Cleanup (void)
        {
                mFileSystem.UnMount ();

                CStdlibAppScreen::Cleanup ();
        }

protected:
        CUSBHCIDevice    mUSBHCI;
        CEMMCDevice     mEMMC;
        CFATFileSystem  mFileSystem;
        CConsole        mConsole;
	CSPIMaster	mSPIMaster;

};

/**
 * Stdlib application that adds network functionality
 * to the CStdlibAppStdio features.
 */
class CStdlibAppNetwork: public CStdlibAppStdio
{
public:
        CStdlibAppNetwork (const char *kernel,
                   const char *pPartitionName = CSTDLIBAPP_DEFAULT_PARTITION,
                   const u8 *pIPAddress      = 0,       // use DHCP if pIPAddress == 0
                   const u8 *pNetMask        = 0,
                   const u8 *pDefaultGateway = 0,
                   const u8 *pDNSServer      = 0)
          : CStdlibAppStdio(kernel, pPartitionName),
            mNet(pIPAddress, pNetMask, pDefaultGateway, pDNSServer)
        {
        }

        virtual bool Initialize (void)
        {
                if (!CStdlibAppStdio::Initialize ())
                {
                        return false;
                }

                return mNet.Initialize ();
        }

protected:
        CScheduler      mScheduler;
        CNetSubSystem   mNet;
};
#endif
