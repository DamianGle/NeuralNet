/*
 * font_png.cpp
 *
 *  Created on: 14 paź 2018
 *      Author: damian
 */

#include <iostream>

#include "../PNG/fonts/DejaVuSans16pt.h"
#include "../PNG/fonts/DejaVuSans16pt_bold.h"
#include "../PNG/fonts/DejaVuSans16pt_bolditalic.h"
#include "../PNG/fonts/DejaVuSans24pt.h"
#include "../PNG/fonts/DejaVuSans24pt_bold.h"
#include "../PNG/fonts/DejaVuSans24pt_bolditalic.h"
#include "../PNG/fonts/DejaVuSans36pt.h"
#include "../PNG/fonts/DejaVuSans36pt_bold.h"
#include "../PNG/fonts/DejaVuSans36pt_bolditalic.h"
#include "../PNG/fonts/DejaVuSans72pt.h"
#include "../PNG/fonts/DejaVuSans72pt_bold.h"
#include "../PNG/fonts/DejaVuSans72pt_bolditalic.h"
#include "../PNG/fonts/DejaVuSans8pt.h"
#include "../PNG/fonts/DejaVuSans8pt_bold.h"
#include "../PNG/fonts/DejaVuSans8pt_bolditalic.h"
#include "../PNG/png_common.h"


FONT_PNG::FONT_PNG()
{
	fonts[0] = {2, 12, 8, DejaVuSans8pt};
	fonts[1] = {2, 12, 8, DejaVuSans8pt_bold};
	fonts[2] = {2, 12, 8, DejaVuSans8pt_bolditalic};
	fonts[3] = {3, 22, 16, DejaVuSans16pt};
	fonts[4] = {3, 22, 16, DejaVuSans16pt_bold};
	fonts[5] = {3, 22, 16, DejaVuSans16pt_bolditalic};
	fonts[6] = {4, 34, 24, DejaVuSans24pt};
	fonts[7] = {5, 34, 24, DejaVuSans24pt_bold};
	fonts[8] = {5, 34, 24, DejaVuSans24pt_bolditalic};
	fonts[9] = {6, 49, 36, DejaVuSans36pt};
	fonts[10] = {7, 49,36, DejaVuSans36pt_bold};
	fonts[11] = {7, 49,36, DejaVuSans36pt_bolditalic};
	fonts[12] = {12, 100, 72, DejaVuSans72pt};
	fonts[13] = {13,  100, 72, DejaVuSans72pt_bold};
	fonts[14] = {13, 100,72, DejaVuSans72pt_bolditalic};
}

void FONT_PNG::write_char(char c, unsigned int font)
{
	for(int i = (c-32)*fonts[font].tab_y * fonts[font].tab_x;
			i <= (c-32)*fonts[font].tab_y * fonts[font].tab_x + fonts[font].tab_y * fonts[font].tab_x - 1;
			i += fonts[font].tab_x)
		{
			for(int y = 0; y <= fonts[font].tab_x - 1; y++)
				{
					for(int z = 0; z <= 7; z++)
						{
							if(((fonts[font].tab_wsk)[i + y]) & (0b10000000 >> z))
								set_pixel();
							set_crs(++crs_x,crs_y);
						}
				}
			crs_x -= fonts[font].tab_x * 8;
			set_crs(crs_x,++crs_y);
		}
}

void FONT_PNG::write_text(std::string text, unsigned int font)
{
	for(unsigned int i = 0; i <= text.size() - 1; i++)
		{
			write_char(text[i], font);
			crs_y -= fonts[font].tab_y;
			crs_x += fonts[font].f_size + 2;
		}
}
