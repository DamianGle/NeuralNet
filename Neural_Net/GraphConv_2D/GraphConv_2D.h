/*
 * GraphConv_2D.h
 *
 *  Created on: 5 sty 2019
 *      Author: damian
 */

#ifndef GRAPHCONV_2D_GRAPHCONV_2D_H_
#define GRAPHCONV_2D_GRAPHCONV_2D_H_

#include <vector>

#include "../Init_small_BPN_Nets/Init_small_BPN_Nets.h"

typedef unsigned char uc;
typedef unsigned int ui;
typedef unsigned long ul;
using namespace std;

class GraphConv_2D : public Initialize_small_BPN_Networks
{
	private:

	public:
	const double Identity[3][3] = 		{0,0,0,		0,1,0,		0,0,0};
	const double Edge_dectect1[3][3] = 	{1,0,-1,	0,0,0,		-1,0,1};
	const double Edge_dectect2[3][3] = 	{0,1,0,		1,-4,1,		0,1,0};
	const double Edge_dectect3[3][3] = 	{-1,-1,-1,	-1,8,-1,	-1,-1,-1};
	const double Sharpen[3][3] = 		{0,-1,0,	-1,5,-1,		0,-1,0};
	const double Sobel_edge_H[3][3] = 		{-1,-2,-1,	0,0,0,		1,2,1};
	const double Sobel_edge_V[3][3] = 		{-1,0,1,	-2,0,2,		-1,0,1};

	GraphConv_2D(string dp);

	void conv_relu__x3(ui *w, ui *h, vector<uc> *src, const double filter[3][3], double factor, double bias);

	void pooling(ui *w, ui *h, vector<uc> *src, ui size, ui set);

	void resend_values_from_nets(string const &dest, ostream & os);
};



#endif /* GRAPHCONV_2D_GRAPHCONV_2D_H_ */
