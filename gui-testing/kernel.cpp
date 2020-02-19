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

#define CANVAS_WIDTH 640
#define CANVAS_HEIGHT 480

#define PLOT_CANVAS_WIDTH 600
#define PLOT_CANVAS_HEIGHT 400

#define HORIZ 0
#define VERT 1
#define dark LV_COLOR_BLACK
#define light lv_color_hex(0x1a1a1a)
#define canvas_color lv_color_hex(0x1a1a1a)
#define bg_color lv_color_hex(0x1a1a1a)

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <exception>
#include <memory>
#include <cassert>

#include "gui.h"

void create_gui(void);

CKernel::CKernel(void)
	: CStdlibAppStdio("RPi-Oscilloscope")
{
	mActLED.Blink(5); // show we are alive
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

CStdlibApp::TShutdownMode CKernel::Run(void)
{
	uint32_t i, j;
	u16 data;
	data = read_adc();
	create_gui();
	mGUI.Update();
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
	
	/*Create a buffer for the canvas*/
	static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(PLOT_CANVAS_WIDTH, PLOT_CANVAS_HEIGHT)];

	/*Create a canvas and initialize its the palette*/
	lv_obj_t *canvas_plot = lv_canvas_create(lv_scr_act(), NULL);
	lv_canvas_set_buffer(canvas_plot, cbuf, PLOT_CANVAS_WIDTH, PLOT_CANVAS_HEIGHT, LV_IMG_CF_INDEXED_1BIT);
	lv_canvas_set_palette(canvas_plot, 0, LV_COLOR_TRANSP);
	lv_canvas_set_palette(canvas_plot, 1, LV_COLOR_YELLOW);
	lv_color_t c0, c1;
	c0.full = 0;
	c1.full = 1;

	while (1)
	{
		/*Clear screen*/
		lv_canvas_fill_bg(canvas_plot, c0);

		/*make one sweep*/
		for (i = 15; i < PLOT_CANVAS_WIDTH; i++)
		{
			for (j = 0; j < 6; j++)
			{
				//mScreen.SetPixel(i, read_adc(), 255);
				lv_canvas_set_px(canvas_plot, i, read_adc(), c1);
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