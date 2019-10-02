/*
 * png.h
 *
 *  Created on: 17 wrz 2018
 *      Author: damian
 */

#ifndef PNG_PNG_COMMON_H_
#define PNG_PNG_COMMON_H_

#include "../PNG/lodepng.h"

typedef unsigned int ui;
typedef unsigned char uc;
using namespace std;

class PNG
{
	private:
		ui error;
		string filename;
		lodepng::State state;

	public:
		vector<uc> buffer;
		vector<uc> image;

		ui w;
		ui h;

	public:
		void getPNGData(const string name);
		void resize_img(vector<uc> *vect, ui *x, ui *y, ui new_x, ui new_y);

		void convert_RGB_to_Grayscale(vector<uc> *vect);
		void negative_filter(vector<uc> *vect);
		void red_filter(vector<uc> *vect);
		void green_filter(vector<uc> *vect);
		void blue_filter(vector<uc> *vect);

		void displayFileInfo();
		void saveNewImage(string new_filename, vector<uc> const& img, ui _w, ui _h);
		void savePixelIntoFile(string filename, vector<uc> *vect, string add, ui set, bool mode = 0);
		void save_image_IntoStringBuffer(string *buffer, vector<uc> *vect, ui set, string add = "");
		void clear_data();
};

class GRAPH_PNG : public PNG
{
	private:
		int r;
		int g;
		int b;
		int a;

	public:
		vector<uc> scrap_image;

		const ui colors_T;
		ui crs_x;
		ui crs_y;

		GRAPH_PNG();

		void set_crs(ui x, ui y);
		void set_pixel_color(int r_, int g_, int b_, int a_);
		void set_pixel_color_fromT(ui num_color);
		void set_pixel();

		void get_scrap_image(int width, int height, vector<uc> *src, vector<uc> *dest);
		void change_raw_color(int r1, int g1, int b1, int a1);

		void line(int X2, int Y2);
		void rectangle(int width, int height);
		void fill_rectangle(int width, int height);
		void round_rect(int width, int height, uint8_t radius, uint8_t fill);
		void circle(int R);
		void fill_circle(int radius);
		void ellipse(long int XRadius, long int YRadius);
};

class FONT_PNG : public GRAPH_PNG
{
	private:
		struct
			{
				int tab_x;
				int tab_y;
				int f_size;
				int *tab_wsk;
			}fonts[15];

		void write_char(char c, ui font);

	public:
		FONT_PNG();

		void write_text(string text, ui font);
};
#endif /* PNG_PNG_COMMON_H_ */
