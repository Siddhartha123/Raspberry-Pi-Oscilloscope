//
// kernel.h
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
#ifndef _kernel_h
#define _kernel_h

#define SPI_CHIP_SELECT 0

#define WINDOW_SIZE 5
#define NOISE

#include <math.h>
#include <circle_stdlib_app.h>

class CKernel : public CStdlibAppScreen
{
public:
	CKernel(void);
	u16 read_adc();
	TShutdownMode Run(void);

private:
	unsigned CANVAS_WIDTH;
	unsigned CANVAS_HEIGHT;
	u8 TxData[2] = {0x0C | 0, 0x00};
	u8 RxBuffer[2];

	//variables for adc data
	long int idx = 0;
	int oldest_idx = 0;
	int samples[WINDOW_SIZE];
	u16 last_sum, data, current_sum;
};

#endif
