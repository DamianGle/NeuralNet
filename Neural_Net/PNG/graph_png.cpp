/*
 * soft_png.cpp
 *
 *  Created on: 27 wrz 2018
 *      Author: damian
 */

#include <iostream>
#include <fstream>

#include "../PNG/png_common.h"
#include "../PNG/user_colors.h"

GRAPH_PNG::GRAPH_PNG() : colors_T(sizeof(PNG_user_colors)/sizeof(int)/4)
{
	r = 0;
	g = 0;
	b = 0;
	a = 0;
	crs_x = 0;
	crs_y = 0;
}

void GRAPH_PNG::set_crs(unsigned int x, unsigned int y)
{
	if(x > w || y > h)
		{
			std::cout << "Cursor out of range!" << std::endl;
			return;
		}
	else
		{
			crs_x = x;
			crs_y = y;
		}
}

void GRAPH_PNG::set_pixel_color(int r_, int g_, int b_, int a_)
{
	r = r_;
	g = g_;
	b = b_;
	a = a_;
}

void GRAPH_PNG::set_pixel_color_fromT(unsigned int num_color)
{
	if(num_color <= sizeof(PNG_user_colors)/sizeof(int)/4)
		{
			r = PNG_user_colors[num_color][0];
			g = PNG_user_colors[num_color][1];
			b = PNG_user_colors[num_color][2];
			a = PNG_user_colors[num_color][3];
		}
	else
		std::cout << "Num of color out of range!" << std::endl;
}

void GRAPH_PNG::set_pixel()
{
	image[(4*crs_x + 0)+(crs_y*w * 4)] = r;
	image[(4*crs_x + 1)+(crs_y*w * 4)] = g;
	image[(4*crs_x + 2)+(crs_y*w * 4)] = b;
	image[(4*crs_x + 3)+(crs_y*w * 4)] = a;
}

void GRAPH_PNG::get_scrap_image(int width, int height,
		std::vector<unsigned char> *src, std::vector<unsigned char> *dest)
{
	std::vector<unsigned char>::iterator it = src->begin();

	for (unsigned int y= crs_y;y<crs_y+height;y++)
	 {
		for (unsigned int x=crs_x;x<crs_x+width;x++)	{
					dest->push_back(it[(4*x + 0)+(y*w * 4)]);
					dest->push_back(it[(4*x + 1)+(y*w * 4)]);
					dest->push_back(it[(4*x + 2)+(y*w * 4)]);
					dest->push_back(it[(4*x + 3)+(y*w * 4)]);
		}
	}
}

void GRAPH_PNG::change_raw_color(int r1, int g1, int b1, int a1)
{
	for(unsigned int y = 0; y <= w*h*4; y+=4)
		{
			if(image[(y + 0)] == r1 && image[(y + 1)] == g1 && image[(y + 2)] == b1 && image[(y + 3)] == a1)
				{
					image[(y + 0)] = r;
					image[(y + 1)] = g;
					image[(y + 2)] = b;
					image[(y + 3)] = a;
				}
		}
}

void GRAPH_PNG::line(int X2, int Y2)
{
	int X1 = crs_x;
	int Y1 = crs_y;

	int CurrentX, CurrentY, Xinc, Yinc,
			Dx, Dy, TwoDx, TwoDy,
			TwoDxAccumulatedError, TwoDyAccumulatedError;

		Dx = (X2-X1);
		Dy = (Y2-Y1);

		TwoDx = Dx + Dx;
		TwoDy = Dy + Dy;

		CurrentX = X1;
		CurrentY = Y1;

		Xinc = 1;
		Yinc = 1;

		if(Dx < 0) {

			Xinc = -1;
			Dx = -Dx;
			TwoDx = -TwoDx;
		}

		if (Dy < 0) {
			Yinc = -1;
			Dy = -Dy;
			TwoDy = -TwoDy;
		}

		set_crs(X1,Y1);
		set_pixel();

		if ((Dx != 0) || (Dy != 0)) {

			if (Dy <= Dx) {
				TwoDxAccumulatedError = 0;
				do {
				    CurrentX += Xinc;
				    TwoDxAccumulatedError += TwoDy;
				    if(TwoDxAccumulatedError > Dx) {
				        CurrentY += Yinc;
				        TwoDxAccumulatedError -= TwoDx;
				    }
				    set_crs(CurrentX,CurrentY);
				    set_pixel();
				  } while (CurrentX != X2);
			  } else {
				  TwoDyAccumulatedError = 0;
				  do {
				      CurrentY += Yinc;
				      TwoDyAccumulatedError += TwoDx;
				      if(TwoDyAccumulatedError>Dy) {
					      CurrentX += Xinc;
					      TwoDyAccumulatedError -= TwoDy;
				      }
				      set_crs(CurrentX,CurrentY);
				      set_pixel();
				  } while (CurrentY != Y2);
			  }
		}
}

void GRAPH_PNG::rectangle(int width, int height)
{
	  int j;
	  int x = crs_x;
	  int y = crs_y;
	  for (j = 0; j < height; j++) {
		  set_crs(x, y + j);
		  set_pixel();
		  set_crs(x + width , y + j);
		  set_pixel();
		}

	  for (j = 0; j < width; j++)	{
		  set_crs(x + j, y);
		  set_pixel();
		  set_crs(x + j, y + height );
		  set_pixel();
		}
}

void GRAPH_PNG::fill_rectangle(int width, int height)
{
	int x, y;
	int y1 = crs_y;
	int x1 = crs_x;

	for (x=x1;x<x1+width;x++) {
		for (y= y1;y<y1+height;y++) {
			set_crs(x,y);
			set_pixel();
		}
	}
}

void GRAPH_PNG::round_rect(int width, int height, uint8_t radius, uint8_t fill)
{
	int16_t tSwitch;
	int x = crs_x;
	int y = crs_y;

  	int x1 = 0, y1 = radius;
  	tSwitch = 3 - 2 * radius;

	while (x1 <= y1) {
		set_crs(x+radius - x1, y+radius - y1);
		set_pixel();
		set_crs(x+radius - y1, y+radius - x1);
		set_pixel();

		set_crs(x+width-radius + x1, y+radius - y1);
		set_pixel();
		set_crs(x+width-radius + y1, y+radius - x1);
		set_pixel();

		set_crs(x+width-radius + x1, y+height-radius + y1);
		set_pixel();
		set_crs(x+width-radius + y1, y+height-radius + x1);
		set_pixel();

		set_crs(x+radius - x1, y+height-radius + y1);
		set_pixel();
		set_crs(x+radius - y1, y+height-radius + x1);
		set_pixel();

		if(fill) {
			set_crs(x+radius - x1, y+radius - y1);
			line(x+width-radius + x1, y+radius - y1);
			set_crs(x+radius - y1, y+radius - x1);
			line(x+width-radius + y1, y+radius - x1);
			set_crs(x+width-radius + x1, y+height-radius + y1);
			line(x+radius - x1, y+height-radius + y1);
			set_crs(x+width-radius + y1, y+height-radius + x1);
			line(x+radius - y1, y+height-radius + x1);
		}

	    if (tSwitch < 0) {
	    	tSwitch += (4 * x1 + 6);
	    } else {
	    	tSwitch += (4 * (x1 - y1) + 10);
	    	y1--;
	    }
	    x1++;
	}

	if(fill) {
		uint16_t i;
		for(i=0; i<height-(2*radius); i++) {
			set_crs(x, y+radius+i);
			line(x+width, y+radius+i);
		}
	}

	set_crs(x+radius, y);
	line(x+width-radius, y);
	set_crs(x+radius, y+height);
	line(x+width-radius, y+height);

	set_crs(x, y+radius);
	line(x, y+height-radius);
	set_crs(x+width, y+radius);
	line(x+width, y+height-radius);
}

void GRAPH_PNG::circle(int R)
{
	   int X, Y, Xchange, YChange, RadiusError;
	   int CX = crs_x;
	   int CY = crs_y;

	   X = R;
	   Y = 0;
	   Xchange = 1 - 2*R;
	   YChange = 1;
	   RadiusError = 0;
	   while( X >= Y ) {
		    set_crs(CX+X, CY+Y);
		    set_pixel();
		    set_crs(CX-X, CY+Y);
		    set_pixel();
		    set_crs(CX-X, CY-Y);
		    set_pixel();
		    set_crs(CX+X, CY-Y);
		    set_pixel();
		    set_crs(CX+Y, CY+X);
		    set_pixel();
		    set_crs(CX-Y, CY+X);
		    set_pixel();
		    set_crs(CX-Y, CY-X);
		    set_pixel();
		    set_crs(CX+Y, CY-X);
		    set_pixel();
	        Y++;
	        RadiusError += YChange;
	        YChange+=2;
	        if ( 2*RadiusError + Xchange > 0 ) {
	              X--;
	              RadiusError+=Xchange;
	              Xchange+=2;
	        }
	   }
}

void GRAPH_PNG::fill_circle(int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;
	int x0 = crs_x;
	int y0 = crs_y;

		set_crs(x0, y0-radius);
		line(x0, y0+radius);

		while(x < y)
		{
			if(f >= 0)
			{
				y--;
				ddF_y += 2;
				f += ddF_y;
			}
			x++;
			ddF_x += 2;
			f += ddF_x;

			set_crs(x0+x, y0+y);
			line(x0+x, y0-y);
			set_crs(x0-x, y0+y);
			line(x0-x, y0-y);
			set_crs(x0+y, y0+x);
			line(y+x0, y0-x);
			set_crs(x0-y, y0+x);
			line(x0-y, y0-x);
	  	}

}

void GRAPH_PNG::ellipse(long int XRadius, long int YRadius)
{
int CX = crs_x;
int CY = crs_y;
		long int X, Y;
		long int XChange, YChange;
		long int EllipseError;
		long int TwoASquare,TwoBSquare;
		long int StoppingX, StoppingY;


		TwoASquare = 2*XRadius*XRadius;
		TwoBSquare = 2*YRadius*YRadius;
		X = XRadius;
		Y = 0;
		XChange = YRadius*YRadius*(1-2*XRadius);
		YChange = XRadius*XRadius;
		EllipseError = 0;
		StoppingX = TwoBSquare*XRadius;
		StoppingY = 0;

		  while ( StoppingX >=StoppingY ) //first set of points,y'>-1
		  {
			   set_crs(CX+X, CY+Y);
			   set_pixel();
			   set_crs(CX-X, CY+Y);
			   set_pixel();
			   set_crs(CX-X, CY-Y);
			   set_pixel();
			   set_crs(CX+X, CY-Y);
			   set_pixel();
		    Y++;
		    StoppingY=StoppingY+ TwoASquare;
		    EllipseError = EllipseError+ YChange;
		    YChange=YChange+TwoASquare;
		    if ((2*EllipseError + XChange) > 0 ) {
		      X--;
		      StoppingX=StoppingX- TwoBSquare;
		      EllipseError=EllipseError+ XChange;
		      XChange=XChange+TwoBSquare;
		    }
		  }
		  Y = YRadius;
		  X = 0;
		  YChange = XRadius*XRadius*(1-2*YRadius);
		  XChange = YRadius*YRadius;
		  EllipseError = 0;
		  StoppingY = TwoASquare*YRadius;
		  StoppingX = 0;

		  while ( StoppingY >=StoppingX )
		  {
			   set_crs(CX+X, CY+Y);
			   set_pixel();
			   set_crs(CX-X, CY+Y);
			   set_pixel();
			   set_crs(CX-X, CY-Y);
			   set_pixel();
			   set_crs(CX+X, CY-Y);
			   set_pixel();

		    X++;
		    StoppingX=StoppingX + TwoBSquare;
		    EllipseError=EllipseError+ XChange;
		    XChange=XChange+TwoBSquare;
		    if ((2*EllipseError + YChange) > 0 ) {
		      Y--;
		      StoppingY=StoppingY- TwoASquare;
		      EllipseError=EllipseError+ YChange;
		      YChange=YChange+TwoASquare;
		    }
		  }
}
