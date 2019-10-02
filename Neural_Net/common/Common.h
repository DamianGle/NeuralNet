/*
 * common.h
 *
 *  Created on: 28 wrz 2018
 *      Author: damian
 */

#ifndef COMMON_COMMON_H_
#define COMMON_COMMON_H_

void save_all_pixels_into_file(std::string map_file, std::string folder_src,
		std::string dest, std::string add, int files = 0);

void create_folder(std::string dir);

#endif /* COMMON_COMMON_H_ */
