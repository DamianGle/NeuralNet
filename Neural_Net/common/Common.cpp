/*
 * commmon.cpp
 *
 *  Created on: 28 wrz 2018
 *      Author: damian
 */

#include <iostream>
#include <string>
#include <fstream>

#include <sys/stat.h>
#include <sys/types.h>

#include "cmdParser.h"

#include "Common.h"

#include "../Files_Tree/Files_Tree.h"
#include "../PNG/png_common.h"

void save_all_pixels_into_file(std::string map_file, std::string folder_src,
		std::string dest, std::string add, int files)
{
	int count = 0;
	std::fstream file;
	std::string str;

	PNG qqq;

	file.open(map_file, std::ios::in | std::ios::out);

	if(file.good())
		{
			file >> str;
			while(!file.eof())
				{
					if((files != 0) && (count ++ == files)) break;
					qqq.getPNGData(folder_src + str);
					qqq.savePixelIntoFile(dest,&qqq.image, add, 1);
					qqq.clear_data();
					file >> str;
				}
			file.close();
		}
}

void create_folder(std::string dir)
{
	mkdir(dir.c_str(), 0777);
}
