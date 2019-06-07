
/*
objects here are like html divs. u have to create objects and then apply style to them. to apply styles, create a style object and then set the object's style. see the example below.
*/
void create_gui(void)
{
	/*Create a style*/
	static lv_style_t style_bg;
	static lv_style_t style_chart;

	//this is the style for background
	style_bg.body.main_color = LV_COLOR_NAVY;
	style_bg.body.grad_color = LV_COLOR_NAVY;
	style_bg.body.opa = 255;
	style_bg.body.border.opa = LV_OPA_50;
	style_bg.text.color = LV_COLOR_RED;

	//this is the style for chart plot area
	style_chart.body.main_color = LV_COLOR_BLACK;
	style_chart.body.grad_color = LV_COLOR_BLACK;
	style_chart.body.opa = 255;
	style_chart.body.border.opa = LV_OPA_50;
	style_chart.text.color = LV_COLOR_RED;

	lv_obj_t *bg = lv_obj_create(lv_scr_act(), NULL);  //bg is a new object
	lv_obj_set_style(bg, &style_bg);
	lv_obj_set_pos(bg, 0, 0);
	lv_obj_set_size(bg, 640, 480);

	lv_obj_t *chart = lv_obj_create(lv_scr_act(), NULL); //chart is a new object
	lv_obj_set_style(chart, &style_chart);
	lv_obj_set_pos(chart, 10, 10);
	lv_obj_set_size(chart, 400, 300);



}
