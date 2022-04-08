// Include header <Self>
#include "../include/Json.h"

// Include header <Important>
#include "../include/File.h"

// Include header <C++>
#include <iostream>
#include <fstream>

/**
 * This function used to get data in target, and replace data
 * from parameter
 */
[[maybe_unused]] void Json::GetData(std::string target, nlohmann::json* data) {
	// Check settings file is exist
	if (File::IsExist(target)) [[likely]] {
		// If exist
		// Get file
		std::ifstream _data_;

	// Open
	_data_.open(target);

	// Convert into json
	_data_ >> *data;

	// Close
	_data_.close();
	}
	else {
		// Show error
		std::cout << "Error settings window: " << target << std::endl;

		// Exit
		exit(1);
	}
}