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

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <exception>
#include <memory>
#include <cassert>

CKernel::CKernel(void)
	: CStdlibAppStdio("RPi-Oscilloscope")
{
	mActLED.Blink(5); // show we are alive
}

u16 CKernel::read_adc(void)
{
	if (mSPIMaster.WriteRead(SPI_CHIP_SELECT, TxData, RxBuffer, 2))
	{
		u16 data = (u16)RxBuffer[0];
		data = data << 4 | RxBuffer[1];
		return data;
	}
	return 0;
}

CStdlibApp::TShutdownMode CKernel::Run(void)
{

	CString Message;
	Message.Format("\n\n\n\n\n\n");

	/*Create a Label on the currently active screen*/
	lv_obj_t *label1 = lv_label_create(lv_scr_act(), NULL);
	u16 data;
	while (1)
	{
		for (volatile unsigned i = 1; i <= 10000000; i++)
			;
		data = read_adc();
		Message.Format("\b\b\b\b\b%4d\n", data);

		/*Modify the Label's text*/
		lv_label_set_text(label1, Message);

		/* Align the Label to the center
        * NULL means align on parent (which is the screen now)
        * 0, 0 at the end means an x, y offset after alignment*/
		lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
		m_GUI.Update();
	}

	return ShutdownHalt;
}