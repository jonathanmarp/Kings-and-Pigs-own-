// Include header <Self>
#include "../include/File.h"

// Include header <C++>
#include <fstream>

/**
 * This function used to check file is
 * Exist or not
 */
bool File::IsExist(std::string path) {
	// Setup
	std::ifstream _data_;

	// Open path
	_data_.open(path);

	// Get is open
	bool isOpen = _data_.is_open();

	// Clsoe
	_data_.close();

	// return data
	return isOpen;
}