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

//canvas dimensions can be multiple of 8

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <exception>
#include <memory>
#include <cassert>

#include "plot.h"
#include "gui.h"

CKernel::CKernel(void)
	: CStdlibAppScreen("RPi-Oscilloscope")
{
	mActLED.Blink(5); // show we are alive
}

CStdlibApp::TShutdownMode CKernel::Run(void)
{
	CANVAS_WIDTH = ((int)((0.853 * mScreen.GetWidth()) / 8)) * 8;
	CANVAS_HEIGHT = ((int)((0.853 * mScreen.GetHeight()) / 8)) * 8;
	create_gui();
	mGUI.Update();

	data = read_adc();
	lv_obj_t *canvas = create_plot_canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
	while (1)
	{
		/*Clear screen*/
		lv_canvas_fill_bg(canvas, c0);

		/*make one sweep*/
		for (i = 10; i < CANVAS_WIDTH; i++)
		{
			for (j = 0; j < 6; j++)
			{
				//mScreen.SetPixel(i, read_adc(), 255);
				lv_canvas_set_px(canvas, i, read_adc(), c1);
			}
		}

		mGUI.Update();

		last_sum = 0;
		for (i = 0; i < WINDOW_SIZE; i++)
			last_sum += samples[i];

		data = read_adc();
		current_sum = 0;
		for (i = 0; i < WINDOW_SIZE; i++)
			current_sum += samples[i];
		while (!(int(abs(data - 230)) < 5 && current_sum > last_sum))
		{
			last_sum = 0;
			for (i = 0; i < WINDOW_SIZE; i++)
				last_sum += samples[i];
			data = read_adc();
			current_sum = 0;
			for (i = 0; i < WINDOW_SIZE; i++)
				current_sum += samples[i];
		}

		for (volatile unsigned i = 1; i <= 10000000; i++)
			;
	}

	return ShutdownHalt;
}

u16 CKernel::read_adc()
{
	idx = idx + 1;
	oldest_idx = (oldest_idx + 1) % WINDOW_SIZE;
	samples[oldest_idx] = (int)(200 + 100 * sin(0.002 * idx));
#ifdef NOISE
	samples[oldest_idx] += (int)(3 * ((double)rand() / (RAND_MAX)));
#endif
	return samples[oldest_idx];
}