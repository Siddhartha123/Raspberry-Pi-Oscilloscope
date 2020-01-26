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

#define CANVAS_WIDTH 800
#define CANVAS_HEIGHT 480

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <exception>
#include <memory>
#include <cassert>

#include"gui.h"

CKernel::CKernel(void)
	: CStdlibAppScreen("RPi-Oscilloscope")
{
	mActLED.Blink(5); // show we are alive
}

CStdlibApp::TShutdownMode CKernel::Run(void)
{
	uint32_t i, j;
	u16 data;
	data = read_adc();
	create_gui();
	static lv_style_t style;
	lv_style_copy(&style, &lv_style_plain);
	style.body.main_color = LV_COLOR_RED;
	style.body.grad_color = LV_COLOR_MAROON;
	style.body.radius = 4;
	style.body.border.width = 2;
	style.body.border.color = LV_COLOR_WHITE;
	style.body.shadow.color = LV_COLOR_WHITE;
	style.body.shadow.width = 4;
	style.line.width = 2;
	style.line.color = LV_COLOR_BLACK;
	style.text.color = LV_COLOR_BLUE;

	static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(CANVAS_WIDTH, CANVAS_HEIGHT)];

	lv_obj_t *canvas = lv_canvas_create(lv_scr_act(), NULL);
	lv_canvas_set_buffer(canvas, cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_TRUE_COLOR);
	lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, 0, 0);
	
	while (1)
	{
		/*Clear screen*/
		lv_canvas_fill_bg(canvas, LV_COLOR_BLACK);

		/*make one sweep*/
		for (i = 15; i < 785; i++)
		{
			for (j = 0; j < 6; j++)
			{
				//mScreen.SetPixel(i, read_adc(), 255);
				lv_canvas_set_px(canvas, i, read_adc(), LV_COLOR_YELLOW);
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
		while (!(int(abs(data - 240)) == 2 && current_sum > last_sum))
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
	while (1)
		;
	return ShutdownHalt;
}

u16 CKernel::read_adc()
{
	idx = idx + 1;
	oldest_idx = (oldest_idx + 1) % WINDOW_SIZE;
	samples[oldest_idx] = (int)(240 + 100 * sin(0.002 * idx));
#ifdef NOISE
	samples[oldest_idx] += (int)(10 * ((double)rand() / (RAND_MAX)));
#endif
	return samples[oldest_idx];
}