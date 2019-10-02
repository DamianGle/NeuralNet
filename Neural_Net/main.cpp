/*
 * main.cpp
 *
 *  Created on: 8 wrz 2018
 *      Author: damian
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <string>
#include <cstring>

#include "BPN_NeuralNetwork/NeuralNetworkTrainer.h"
#include "BPN_NeuralNetwork/TrainingDataReader.h"
#include "common/Common.h"
#include "Files_Tree/Files_Tree.h"
#include "GraphConv_2D/GraphConv_2D.h"
#include "PNG/png_common.h"


int main(void)
{
	vector<unsigned char> vect,vect2;
	string rrr;
	unsigned long new_x = 0, new_y = 0;

	GRAPH_PNG png;
	png.getPNGData("5.png");
	png.save_image_IntoStringBuffer(&rrr,&png.image, 1);

	GraphConv_2D conv("../../networks_roboczy");
	conv.search_networks(cout);
	conv.check_files(cout);
	conv.initialize_values(cout);
	conv.resend_values_from_nets(rrr, cout);

//	GraphConv_2D conv("../../networks_roboczy");
//	conv.conv_relu__x3(&png.w, &png.h, &png.image, conv.Sobel_edge_H, 1.0, 1.0);
//	png.saveNewImage("dddss.png", png.image, png.w, png.h);

//	GraphConv_2D conv("../../networks_roboczy");
//	conv.pooling(&png.w, &png.h, &png.image, 2, 2);
//	png.saveNewImage("avg1.png", png.image, png.w, png.h);

//	GraphConv_2D conv("../../networks_roboczy");
//	conv.conv_relu__x3(png.w, png.h, png.image,&new_x, &new_y, &vect, conv.Sobel_edge_H, 1.0, 1.0);
//	conv.min_pooling(new_x, new_y, vect, &new_x, &new_y, &vect2, 2);
//	png.saveNewImage("ss.png", vect2, new_x, new_y);

//	GraphConv_2D conv("../../networks_roboczy");
//	conv.train_network("neuronkii");





//	save_all_pixels_into_file("/home/damian_g/Pulpit/0_9_mono_png/1_set/map_file_0.txt",
//		"/home/damian_g/Pulpit/0_9_mono_png/1_set/0/","sets.txt", "1,0,0,0,0,0,0,0,0,0");


	//	Katalog k("../../0_9_mono_png/2_set/9/");
//	k.drukuj();

	return 0;
}
