/*
 * Graph_Conv_2D.cpp
 *
 *  Created on: 5 sty 2019
 *      Author: damian
 */

#include "../GraphConv_2D/GraphConv_2D.h"

#include <iostream>
#include <string>
#include <fstream>

#include "../PNG/png_common.h"

GraphConv_2D::GraphConv_2D(string dp) : Initialize_small_BPN_Networks(dp)
{

}

void GraphConv_2D::conv_relu__x3(ui *w, ui *h, vector<uc> *src, const double filter[3][3],
									double factor, double bias)
{
	std::vector<uc>::iterator it = src->begin();
	vector<uc> tmp;

	for(ui i = 0; i <= src->size(); i++)
		tmp.push_back(it[i]);

	src->clear();

	ui tmp_w = *w;
	ui tmp_h = *h;

	for(ul y = 0; y < tmp_h; y++)
		{
			for(ul x = 0; x < tmp_w; x++)
				{
					double red = 0.0, green = 0.0, blue = 0.0;

					for(ui filterY = 0; filterY < 3; filterY++)
						{
							for(ui filterX = 0; filterX < 3; filterX++)
								{
									int imageX = (x - 3 / 2 + filterX + (tmp_w )) % (tmp_w);
									int imageY = (y - 3 / 2 + filterY + tmp_h) % tmp_h;

									red += tmp[imageY*tmp_w*4 + (imageX*4 + 0)] * filter[filterY][filterX];
									green += tmp[imageY*tmp_w*4 + (imageX*4 + 1)] * filter[filterY][filterX];
									blue += tmp[imageY*tmp_w*4 + (imageX*4 + 2)] * filter[filterY][filterX];
								}
						}
					src->push_back(min(max(int(factor*red + bias),0),255));	// R
					src->push_back(min(max(int(factor*green + bias),0),255));	// G
					src->push_back(min(max(int(factor*blue + bias),0),255));	// B
					src->push_back(255);										// A
				}
		}
	*w = tmp_w;
	*h = tmp_h;
}

void GraphConv_2D::pooling(ui *w, ui *h, vector<uc> *src, ui size, ui set)
{
	std::vector<uc>::iterator it = src->begin();
	vector<uc> tmp;

	for(ui i = 0; i <= src->size(); i++)
		tmp.push_back(it[i]);

	src->clear();

	ui tmp_w = *w;
	ui tmp_h = *h;

	for(ul y = 0; y <= tmp_h - size; y+=size)
		{
			for(ul x = 0; x <= tmp_w - size; x+=size)
				{
					double r = 0.0 , g = 0.0, b = 0.0;

					if(set == 1)
						{
							r = 255.0 , g = 255.0, b = 255.0;
						}

					for(ui filterY = 0; filterY < size; filterY++)
						{
							for(ui filterX = 0; filterX < size; filterX++)
							{
									int imageX = (x - size / 2 + filterX + (tmp_w )) % (tmp_w);
									int imageY = (y - size / 2 + filterY + tmp_h) % tmp_h;

									if(set == 0)
										{
											if(tmp[imageY*tmp_w*4 + (imageX*4 + 0)] >= r)
												r = tmp[imageY*tmp_w*4 + (imageX*4 + 0)];

											if(tmp[imageY*tmp_w*4 + (imageX*4 + 1)] >= g)
												g = tmp[imageY*tmp_w*4 + (imageX*4 + 1)];

											if(tmp[imageY*tmp_w*4 + (imageX*4 + 2)] >= b)
												b = tmp[imageY*tmp_w*4 + (imageX*4 + 2)];
										}
									if(set == 1)
										{
											if(tmp[imageY*tmp_w*4 + (imageX*4 + 0)] < r)
												r = tmp[imageY*tmp_w*4 + (imageX*4 + 0)];

											if(tmp[imageY*tmp_w*4 + (imageX*4 + 1)] < g)
												g = tmp[imageY*tmp_w*4 + (imageX*4 + 1)];

											if(tmp[imageY*tmp_w*4 + (imageX*4 + 2)] < b)
												b = tmp[imageY*tmp_w*4 + (imageX*4 + 2)];
										}
									if(set == 2)
										{
											r += tmp[imageY*tmp_w*4 + (imageX*4 + 0)] / size;
											g += tmp[imageY*tmp_w*4 + (imageX*4 + 1)] / size;
											b += tmp[imageY*tmp_w*4 + (imageX*4 + 2)] / size;
										}
								}
						}
					src->push_back(r);	// R
					src->push_back(g);	// G
					src->push_back(b);	// B
					src->push_back(255);   // A
				}
		}
	*w = tmp_w / size;
	*h = tmp_h / size;
}

void GraphConv_2D::resend_values_from_nets(string const &dest, ostream & os)
{
	for(unsigned int i = 0; i <= Network_name.size() - 1; i++)
		{
			BPN::Network nn( NetworkSettings[i], 2, buffer_weights[i]);

			BPN::NetworkTrainer trainer(TrainerSettings[i], &nn);
			trainer.m_maxEpochs = 1;

			BPN::TrainingDataReader dataReader(" ", NetworkSettings[i].m_numInputs, NetworkSettings[i].m_numOutputs );

			string zeros = ",0";
			for(unsigned int z = 2; z <= NetworkSettings[i].m_numOutputs; z++)
				zeros.append(",0");

			if ( !dataReader.ReadData_from_Buffer(dest + zeros,1) )
				return;

			trainer.Train( dataReader.GetTrainingData(), 1);

			for(unsigned int zz = 0; zz <= nn.m_outputNeurons.size() - 1; zz++)
				os << nn.m_outputNeurons[zz] << ',';

			nn.LoadWeightsFromBuffer(buffer_weights[i]);
			os << '\n';
		}
}

