#define HORIZ 0
#define VERT 1
#define LARGE
#define dark LV_COLOR_BLACK
#define light LV_COLOR_HEX(0x1a1a1a)
#define canvas_color LV_COLOR_HEX(0x1a1a1a)
#define bg_color LV_COLOR_HEX(0x1a1a1a)

//Defining Screensize and Grid Size
#ifdef LARGE
#define H 600
#define W 900
#define SH 720
#define SW 1280
#endif // LARGE

/*Create a style*/
static lv_style_t style_bg;
static lv_style_t style_chart;
static lv_style_t style_txt;
static lv_style_t style_btn1, style_btn2, style_btn3, style_btn4;
static lv_style_t style_bch1, style_bch2, style_bch3, style_bch4;

void create_gui(void)
{
    //Style for buttons
	style_btn1.body.main_color = light;
	style_btn1.body.grad_color = light;
	style_btn1.body.border.width = 2;
	style_btn1.body.border.part = LV_BORDER_FULL;
	style_btn1.body.border.opa = 255;
	style_btn1.body.opa = 255;

	lv_style_copy(&style_btn2, &style_btn1);
	lv_style_copy(&style_bch1, &style_btn1);
	lv_style_copy(&style_bch2, &style_btn1);
	lv_style_copy(&style_btn3, &style_btn1);
	lv_style_copy(&style_bch3, &style_btn1);
	lv_style_copy(&style_btn4, &style_btn1);
	lv_style_copy(&style_bch4, &style_btn1);

	style_bch1.body.main_color = LV_COLOR_YELLOW;
	style_bch1.body.grad_color = LV_COLOR_YELLOW;
	style_btn1.body.border.color = LV_COLOR_YELLOW;
	style_bch1.body.border.color = LV_COLOR_YELLOW;
	style_bch2.body.main_color = LV_COLOR_CYAN;
	style_bch2.body.grad_color = LV_COLOR_CYAN;
	style_btn2.body.border.color = LV_COLOR_CYAN;
	style_bch2.body.border.color = LV_COLOR_CYAN;
	style_bch3.body.main_color = LV_COLOR_PURPLE;
	style_bch3.body.grad_color = LV_COLOR_PURPLE;
	style_btn3.body.border.color = LV_COLOR_PURPLE;
	style_bch3.body.border.color = LV_COLOR_PURPLE;
	style_bch4.body.main_color = LV_COLOR_BLUE;
	style_bch4.body.grad_color = LV_COLOR_BLUE;
	style_btn4.body.border.color = LV_COLOR_BLUE;
	style_bch4.body.border.color = LV_COLOR_BLUE;

	//Style for background
	style_bg.body.main_color = bg_color;
	style_bg.body.grad_color = bg_color;
	style_bg.body.opa = 255;
	style_bg.body.border.opa = LV_OPA_50;
	style_bg.text.color = LV_COLOR_WHITE;

	//Style for chart plot area
	style_chart.body.main_color = light;
	style_chart.body.grad_color = light;
	style_chart.body.opa = 255;
	style_chart.body.border.opa = LV_OPA_50;
	style_chart.text.color = LV_COLOR_WHITE;

    //Style for texts
    style_txt.text.font = &lv_font_dejavu_40;
    style_txt.text.letter_space = 2;
    style_txt.text.line_space = 1;
	style_txt.text.color = LV_COLOR_BLACK;
	style_txt.text.opa = 255;

	//Creating the background and chart
	lv_obj_t *bg = lv_obj_create(lv_scr_act(), NULL);  //bg is a new object
	lv_obj_set_style(bg, &style_bg);
	lv_obj_set_pos(bg, 0, 0);
	lv_obj_set_size(bg, 1280, 720);

	lv_obj_t *footer_bg = lv_obj_create(lv_scr_act(), NULL); //chart is a new object
	lv_obj_set_style(footer_bg, &style_chart);
	lv_obj_set_pos(footer_bg, 0, 660);
	lv_obj_set_size(footer_bg, 1280, 60);

	lv_obj_t *domain = lv_obj_create(lv_scr_act(), NULL); //chart is a new object
	lv_obj_set_style(domain, &style_chart);
	lv_obj_set_pos(domain, 0, 0);
	lv_obj_set_size(domain, 1280, 60);

    /*================================================================*/
    /*Create Buttons*/
    lv_obj_t *btn1 = lv_obj_create(footer_bg, NULL);
    lv_obj_set_click(btn1, true);
    lv_obj_t *bch1 = lv_obj_create(btn1, NULL);
    lv_obj_t *label1 = lv_label_create(bch1, NULL);
    lv_obj_set_style(btn1, &style_btn1);
    lv_obj_set_style(bch1, &style_bch1);
    channelButton(btn1, bch1, label1, 1);
    lv_obj_t *btn2 = lv_obj_create(footer_bg, NULL);
    lv_obj_set_click(btn2, true);
    lv_obj_t *bch2 = lv_obj_create(btn2, NULL);
    lv_obj_t *label2 = lv_label_create(bch2, NULL);
    lv_obj_set_style(btn2, &style_btn2);
    lv_obj_set_style(bch2, &style_bch2);
    channelButton(btn2, bch2, label2, 2);
    lv_obj_t *btn3 = lv_obj_create(footer_bg, NULL);
    lv_obj_set_click(btn3, true);
    lv_obj_t *bch3 = lv_obj_create(btn3, NULL);
    lv_obj_t *label3 = lv_label_create(bch3, NULL);
    lv_obj_set_style(btn3, &style_btn3);
    lv_obj_set_style(bch3, &style_bch3);
    channelButton(btn3, bch3, label3, 3);
    lv_obj_t *btn4 = lv_obj_create(footer_bg, NULL);
    lv_obj_set_click(btn4, true);
    lv_obj_t *bch4 = lv_obj_create(btn4, NULL);
    lv_obj_t *label4 = lv_label_create(bch4, NULL);
    lv_obj_set_style(btn4, &style_btn4);
    lv_obj_set_style(bch4, &style_bch4);
    channelButton(btn4, bch4, label4, 4);

    /*================================================================*/
    /*Create a buffer for the canvas set its pixels to light blue*/
    static lv_color_t cbuf[sizeof(lv_color_t) * (W+1) * (H+1)];
    uint32_t i;
    for(i = 0; i < sizeof(cbuf) / sizeof(cbuf[0]); i++)
        cbuf[i] = canvas_color;

    /*Create the canvas object*/
    lv_obj_t * canvas = lv_canvas_create(lv_scr_act(), NULL);
    lv_obj_set_pos(canvas, 60, 60);

    /*Assign the buffer to the canvas*/
    lv_canvas_set_buffer(canvas, cbuf, W+1, H+1, LV_IMG_CF_TRUE_COLOR);

    /* draw grid lines in the chart area*/
//    for (int i = 0; i <= W; i+=W/12)
//			drawDashedLine(i, 1, 2, 2, canvas);
//
//	for (int i = 0; i <= H; i+=H/8)
//			drawDashedLine(i, 0, 2, 2, canvas);
//
//	centerLine(H / 2, 0, 8, canvas);
//	centerLine(W / 2, 1, 8, canvas);
//	edgeMarker(0, 1, 14, 0, canvas);
//	edgeMarker(W, 1, 14, 1, canvas);
//	edgeMarker(0, 0, 14, 0, canvas);
//	edgeMarker(H, 0, 14, 1, canvas);

	/*===============================================================*/
	/*Side menu*/
    lv_obj_t * cont;

        cont = lv_cont_create(lv_scr_act(), NULL);
        lv_obj_set_auto_realign(cont, true);                    /*Auto realign when the size changes*/
        lv_obj_align_origo(cont, NULL, LV_ALIGN_CENTER, 0, 0);  /*This parametrs will be sued when realigned*/
        lv_cont_set_fit(cont, LV_FIT_TIGHT);
        lv_cont_set_layout(cont, LV_LAYOUT_COL_M);

        lv_obj_t * label;
        label = lv_label_create(cont, NULL);
        lv_label_set_text(label, "Short text");

        label = lv_label_create(cont, NULL);
        lv_label_set_text(label, "It is a long text");

        label = lv_label_create(cont, NULL);
        lv_label_set_text(label, "Here is an even longer text");

}

void edgeMarker(int dist, int orientation, int width, bool flag, lv_obj_t * canvas) {
	if (flag) {
		if (orientation == HORIZ) {
			for (int i = 0; i <= W; i += W / 60) {
				for (int j = 0; j < width / 2; j++)
					lv_canvas_set_px(canvas, i,dist - j, LV_COLOR_WHITE);
			}
		}
		if (orientation == VERT) {
			for (int i = 0; i <= H; i += H / 40) {
				for (int j = 0; j < width / 2; j++)
					lv_canvas_set_px(canvas, dist - j, i, LV_COLOR_WHITE);
			}
		}
	}
	else {
		if (orientation == HORIZ) {
			for (int i = 0; i <= W; i += W / 60) {
				for (int j = 0; j < width / 2; j++)
					lv_canvas_set_px(canvas, i, dist + j, LV_COLOR_WHITE);
			}
		}
		if (orientation == VERT) {
			for (int i = 0; i <= H; i += H / 40) {
				for (int j = 0; j < width / 2; j++)
					lv_canvas_set_px(canvas, dist + j, i, LV_COLOR_WHITE);
			}
		}
	}
}

void drawDashedLine(int coord,int type,int dot,int space, lv_obj_t * canvas) {
	int i = 0;
	if (type == HORIZ) {
		for (i = 0;i < W;i++) {
			if (i%dot < (dot - 1))
				lv_canvas_set_px(canvas, i, coord, LV_COLOR_WHITE);
			else
				i = i + space;
		}
	}

	if (type == VERT) {
		for (i = 0;i < H;i++) {
			if (i%dot < (dot - 1))
				lv_canvas_set_px(canvas, coord, i, LV_COLOR_WHITE);
			else
				i = i + space;
		}
	}
}

void centerLine(int dist, int orientation, int width, lv_obj_t * canvas) {
	if (orientation == HORIZ) {
		for (int i = 0; i <= W; i+=W/60) {
			for (int j = 0; j < width/2; j++) {
				lv_canvas_set_px(canvas, i,dist + j, LV_COLOR_WHITE);
				lv_canvas_set_px(canvas, i,dist - j, LV_COLOR_WHITE);
			}
		}
	}
	if (orientation == VERT) {
		for (int i = 0; i <= H; i += H / 40) {
			for (int j = 0; j < width / 2; j++) {
				lv_canvas_set_px(canvas, dist + j, i, LV_COLOR_WHITE);
				lv_canvas_set_px(canvas, dist - j, i, LV_COLOR_WHITE);
			}
		}
	}
}

void channelButton(lv_obj_t * btn1, lv_obj_t * bch1, lv_obj_t * label1, int channel) {
    char buffer[2];
    //itoa(channel, buffer, 10);
    lv_obj_set_pos(btn1, (channel-1)*256, 10);
    lv_obj_set_size(btn1, 252, 50);
    lv_obj_set_pos(bch1, 0, 0);
    lv_obj_set_size(bch1, 57, 60);
    lv_label_set_text(label1, buffer);
    lv_obj_set_style(label1, &style_txt);
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
}
