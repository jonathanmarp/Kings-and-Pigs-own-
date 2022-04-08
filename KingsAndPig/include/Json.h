#ifndef JSON_H
#define JSON_H

// Include header <C++>
#include <string>

// Include header <3party>
#include <nlohmann/json.hpp>

class Json {
public:
	/**
	 * This function used to get data in target, and replace data
	 * from parameter
	 */
	[[maybe_unused]] static void GetData(std::string target, nlohmann::json* data);
};

#endif // JSON_H