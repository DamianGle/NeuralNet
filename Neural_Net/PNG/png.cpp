/*
 * png.cpp
 *
 *  Created on: 17 wrz 2018
 *      Author: damian
 */

#include <iostream>
#include <fstream>
#include <cmath>

#include "../PNG/png_common.h"

void PNG::getPNGData(const string name)
{
	filename = name;

	lodepng::load_file(buffer, filename);
    error = lodepng::decode(image, w, h, state, buffer);

    if(error)
    	cout << "decoder error " << error << ": " << lodepng_error_text(error) << endl;

    cout << "File name: " << filename << endl;
}

void PNG::resize_img(vector<uc> *vect, ui *x, ui *y, ui new_x, ui new_y)
{
	vector<uc>::iterator it = vect->begin();
	vector<uc> tmp;

	for(ui i = 0; i <= vect->size(); i++)
		tmp.push_back(it[i]);

	vect->clear();

	ui tmp_w = *x;
	ui tmp_h = *y;

	double scaleWidth =  (double)new_x / (double)tmp_w;
	double scaleHeight = (double)new_y / (double)tmp_h;

    for(ui cy = 0; cy < new_y; cy++)
    {
        for(ui cx = 0; cx < new_x; cx++)
        {
            int nearestMatch =  (((int)(cy / scaleHeight) * (tmp_w *4)) + ((int)(cx / scaleWidth) *4) );

            vect->push_back(tmp[nearestMatch + 0]);
            vect->push_back(tmp[nearestMatch + 1]);
            vect->push_back(tmp[nearestMatch + 2]);
            vect->push_back(tmp[nearestMatch + 3]);
        }
    }
    *x = new_x;
    *y = new_y;
}

void PNG::convert_RGB_to_Grayscale(vector<uc> *vect)
{
	uc grey = 0;
	std::vector<uc>::iterator it = vect->begin();

	for(ui i = 0; i <= vect->size() - 1; i += 4)
		{
			grey = ( (double)(it[i + 0])*0.299 + (double)it[i + 1]*0.587 + (double)it[i + 2]*0.114 );
			it[i + 0] = grey;
			it[i + 1] = grey;
			it[i + 2] = grey;
		}

}

void PNG::negative_filter(std::vector<uc> *vect)
{
	vector<uc>::iterator it = vect->begin();

	for(ui i = 0; i <= vect->size() - 1; i+=4)
		{
			it[i + 0] = 255-it[i + 0];
			it[i + 1] = 255-it[i + 1];
			it[i + 2] = 255-it[i + 2];
		}
}

void PNG::red_filter(std::vector<uc> *vect)
{
	vector<uc>::iterator it = vect->begin();

	for(ui i = 0; i <= vect->size() - 1; i+=4)
		{
			it[i + 1] = 0;
			it[i + 2] = 0;
		}
}

void PNG::green_filter(vector<uc> *vect)
{
	vector<uc>::iterator it = vect->begin();

	for(ui i = 0; i <= vect->size() - 1; i+=4)
		{
			it[i + 0] = 0;
			it[i + 2] = 0;
		}
}

void PNG::blue_filter(vector<uc> *vect)
{
	vector<uc>::iterator it = vect->begin();

	for(ui i = 0; i <= vect->size() - 1; i+=4)
		{
			it[i + 0] = 0;
			it[i + 1] = 0;
		}
}

void PNG::displayFileInfo()
{
	cout << "Filesize: " << buffer.size() << " (" << buffer.size() / 1024 << "K)" << endl;
	cout << "Width: " << w << endl;
	cout << "Height: " << h << endl;
	cout << "Num pixels: " << w * h << endl;

	if(w > 0 && h > 0)
		{
	    	cout << "Top left pixel color:"
	    		 << " r: " << (int)image[0]
	             << " g: " << (int)image[1]
	             << " b: " << (int)image[2]
	             << " a: " << (int)image[3]
	             << endl;
	    }
}

void PNG::saveNewImage(string new_filename, vector<uc> const& img, ui _w, ui _h)
{
	vector<uc> buffer1;

	error = lodepng::encode(buffer1,img, _w, _h);
	if(error)
		{
			cout << "encoder error " << error << ": "<< lodepng_error_text(error) << endl;
		    return;
		}
	lodepng::save_file(buffer1, new_filename);
}

void PNG::savePixelIntoFile(string filename, vector<uc> *vect, string add, ui set, bool mode)
{
	vector<uc>::iterator it = vect->begin();
	fstream file;

	if(!mode) file.open( filename, ios::in | ios::out | ios::app );
	else file.open( filename, ios::in | ios::out | ios::trunc );

	if(file.good() == true)
		{
			if(set == 0)
				for(ui i = 0; i <= vect->size() - 1; i++)
					file << (ui)it[i] << ',';

			if(set == 1)
				{
					unsigned char grey = 0;

					for(unsigned int i = 0; i <= vect->size() - 1; i += 4)
						{
							grey = ( (double)it[i + 0]*0.299 +
									 (double)it[i + 1]*0.587 +
									 (double)it[i + 2]*0.114  );

							file << (unsigned int)grey << ',';
						}
				}

			if(set == 2)
				for(unsigned int i = 0; i <= vect->size() - 1; i += 4)
					file << (unsigned int)it[i] << ',';
			if(set == 3)
				for(unsigned int i = 0; i <= vect->size() - 1; i += 4)
					file << (unsigned int)it[i + 1] << ',';
			if(set == 4)
				for(unsigned int i = 0; i <= vect->size() - 1; i += 4)
					file << (unsigned int)it[i + 2] << ',';

			file << add << std::endl;
		}
	else
		std::cout << "File doesn't exist!" << std::endl;
	file.close();
}


void PNG::save_image_IntoStringBuffer(std::string *buffer,std::vector<unsigned char> *vect,
		 unsigned int set, std::string add)
{
	std::vector<unsigned char>::iterator it = vect->begin();

	if(set == 0)
		{
			for(unsigned int i = 0; i <= vect->size() - 1; i++)
				{
					buffer->append(std::to_string((unsigned int)it[i]));
					buffer->append(",");
				}
		}
	if(set == 1)
		{
			unsigned char grey = 0;

			for(unsigned int i = 0; i <= vect->size() - 1; i += 4)
				{
					grey = ( (double)it[i + 0]*0.299 +
							 (double)it[i + 1]*0.587 +
							 (double)it[i + 2]*0.114  );

					buffer->append(std::to_string((unsigned int)grey));
					buffer->append(",");
				}
		}
		if(set == 2)
			{
				for(unsigned int i = 0; i <= vect->size() - 1; i += 4)
					{
						buffer->append(std::to_string((unsigned int)it[i]));
						buffer->append(",");
					}
			}
		if(set == 3)
			{
				for(unsigned int i = 0; i <= vect->size() - 1; i += 4)
					{
						buffer->append(std::to_string((unsigned int)it[i + 1]));
						buffer->append(",");
					}
			}
		if(set == 4)
			{
				for(unsigned int i = 0; i <= vect->size() - 1; i += 4)
					{
						buffer->append(std::to_string((unsigned int)it[i + 2]));
						buffer->append(",");
					}
			}
	buffer->append(add);
	buffer->append("\n");
}

void PNG::clear_data()
{
	w = 0;
	h = 0;

	buffer.erase( buffer.begin(), buffer.end() );
	image.erase( image.begin(), image.end() );
}
