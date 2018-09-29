//
// kernel.cpp
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include "kernel.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

#define SPI_CLOCK_SPEED 32000 // Hz
#define SPI_CPOL 0
#define SPI_CPHA 0
#define SPI_CHIP_SELECT 0 // Mode 0

u8 TxData[2] = {0x0C | 0, 0x00};
u8 RxBuffer[2];
u16 data;

CKernel::CKernel(void)
	: CStdlibAppScreen("RPi-Oscilloscope")
{
	mActLED.Blink(5); // show we are alive
}

u16 read_adc(CSPIMaster mSPIMaster)
{
	if (mSPIMaster.WriteRead(SPI_CHIP_SELECT, TxData, RxBuffer, 2))
	{
		data = (u16)RxBuffer[0];
		data = data << 4 | RxBuffer[1];
		return data;
	}
	else
		return -1;
}

void CKernel::DoLongJmp(void)
{
	longjmp(m_JumpBuf, 42);
}

CStdlibApp::TShutdownMode CKernel::Run(void)
{
	u16 d = 0;
	CString Message;
	Message.Format("\n\n\n\n\n\n");
	while (1)
	{
		d = read_adc(mSPIMaster);
		Message.Format("\b\b\b\b\b%4d\n", d);
		mScreen.Write((const char *)Message, Message.GetLength());
	}
	return ShutdownReboot;
}
