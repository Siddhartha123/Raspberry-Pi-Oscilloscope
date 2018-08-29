#include "kernel.h"
#include <circle/debug.h>

#define SPI_CLOCK_SPEED 2000000 // Hz
#define SPI_CPOL 0
#define SPI_CPHA 0
#define SPI_CHIP_SELECT 0 // Mode 0

static const char FromKernel[] = "kernel";

CKernel::CKernel(void)
	: m_Screen(m_Options.GetWidth(), m_Options.GetHeight()),
	  m_Timer(&m_Interrupt),
	  m_Logger(m_Options.GetLogLevel(), &m_Timer),
	  m_SPIMaster(SPI_CLOCK_SPEED, SPI_CPOL, SPI_CPHA)
{
	m_ActLED.Blink(1);
}

CKernel::~CKernel(void)
{
}

boolean CKernel::Initialize(void)
{
	boolean bOK = TRUE;

	if (bOK)
	{
		bOK = m_Screen.Initialize();
	}

	if (bOK)
	{
		bOK = m_Serial.Initialize(115200);
	}

	if (bOK)
	{
		CDevice *pTarget = m_DeviceNameService.GetDevice(m_Options.GetLogDevice(), FALSE);
		if (pTarget == 0)
		{
			pTarget = &m_Screen;
		}

		bOK = m_Logger.Initialize(pTarget);
	}

	if (bOK)
	{
		bOK = m_Interrupt.Initialize();
	}

	if (bOK)
	{
		bOK = m_Timer.Initialize();
	}

	if (bOK)
	{
		bOK = m_SPIMaster.Initialize();
	}

	return bOK;
}

TShutdownMode CKernel::Run(void)
{

	u8 TxData[2] = {0x0C | 0, 0x00};
	u8 RxBuffer[2];
	u16 data;
	CString Message;
	Message.Format("\n\n\n\n\n\n");
	while (1)
	{
		if (m_SPIMaster.WriteRead(SPI_CHIP_SELECT, TxData, RxBuffer, 2))
		{
			for (volatile unsigned i = 1; i <= 10000000; i++)
			{
				// just wait
			}
			data = (u16)RxBuffer[0];
			data = data << 4 | RxBuffer[1];
			Message.Format("\b\b\b\b\b%4d\n", data);
			m_Screen.Write((const char *)Message, Message.GetLength());
		}
		else
		{
			Message.Format("error");
			m_Screen.Write((const char *)Message, Message.GetLength());
		}
	}
	return ShutdownHalt;
}
