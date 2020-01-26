#include "screen.h"
#include "plot.h"

using namespace std;

/*
void CursorMove (unsigned nRow, unsigned nColumn);
TScreenColor
void Rotor (unsigned nIndex, unsigned nCount);
*/
int main()
{

    double t = 0;
    Screen m_screen(640, 480);
    int i;

    //variables for adc data
    long int idx = 0;
    int oldest_idx = 0;
    int samples[WINDOW_SIZE];
    int last_sum, data, current_sum;
    m_screen.display();

    while (!m_screen.finish)
    {
        //do stuff here
        // t++;
        // if ((int)t % 640 == 0)
        //     m_screen.clear();
        // m_screen.SetPixel((int)t % 640, (int)(240 + 100 * sin(0.02 * t)));

        m_screen.clear();

        scan(&m_screen, idx, oldest_idx, samples);

        m_screen.update();
        last_sum = 0;
        for (i = 0; i < WINDOW_SIZE; i++)
            last_sum += samples[i];

        data = read_adc(idx, oldest_idx, samples);

        current_sum = 0;
        for (i = 0; i < WINDOW_SIZE; i++)
            current_sum += samples[i];
        while (!(int(abs(data - 240)) == 2 && current_sum > last_sum))
        {
            last_sum = 0;
            for (i = 0; i < WINDOW_SIZE; i++)
                last_sum += samples[i];
            data = read_adc(idx, oldest_idx, samples);
            current_sum = 0;
            for (i = 0; i < WINDOW_SIZE; i++)
                current_sum += samples[i];
        }
        usleep(100000);
    }
    return 0;
}