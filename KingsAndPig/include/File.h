#ifndef FILE_H
#define FILE_H

// Include header <C++>
#include <string>

class File {
public:
	/**
	 * This function used to check file is
	 * Exist or not
	 */
	[[maybe_unused]] static bool IsExist(std::string path);
};

#endif // FILE_H