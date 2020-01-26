#define WINDOW_SIZE 5
#define NOISE

int read_adc(long int &idx, int &oldest_idx, int *samples)
{
    idx = idx + 1;
    oldest_idx = (oldest_idx + 1) % WINDOW_SIZE;
    samples[oldest_idx] = (int)(240 + 100 * sin(0.02 * idx));
#ifdef NOISE
    samples[oldest_idx] += (int)(30 * ((double)rand() / (RAND_MAX)));
#endif
    return samples[oldest_idx];
}

void scan(Screen *m_screen, long int &idx, int &oldest_idx, int *samples)
{
    int i, j;
    for (i = 15; i < 515; i++)
    {
        for (j = 0; j < 6; j++)
        {
            (*m_screen).SetPixel(i, read_adc(idx, oldest_idx, samples));
        }
    }
}
