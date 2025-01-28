#pragma once
#include <vector>
#include <string>
#include <unordered_map>

//standart dataTypes for xml utilize

namespace dataTypes {
	using attributes = std::vector<std::string>;
	using data = std::unordered_multimap<size_t,std::vector<std::string>>;
}

