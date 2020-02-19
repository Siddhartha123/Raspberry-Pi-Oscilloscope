#define PLOT_H 380
#define PLOT_W 540

uint32_t i, j;
u16 data;
/*Create colors with the indices of the palette*/
lv_color_t c0, c1;

lv_obj_t* create_plot_canvas(unsigned CANVAS_WIDTH, unsigned CANVAS_HEIGHT)
{
    /*Create a buffer for the canvas*/
    //make this static
    lv_color_t cbuf[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(CANVAS_WIDTH, CANVAS_HEIGHT)];

    /*Create a canvas and initialize its the palette*/
    lv_obj_t *canvas = lv_canvas_create(lv_scr_act(), NULL);
    lv_canvas_set_buffer(canvas, cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_INDEXED_1BIT);
    lv_canvas_set_palette(canvas, 0, LV_COLOR_TRANSP);
    lv_canvas_set_palette(canvas, 1, LV_COLOR_YELLOW);

    c0.full = 0;
    c1.full = 1;
    return canvas;
}