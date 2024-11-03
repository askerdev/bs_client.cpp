#include "types.h"
#include <sstream>
#include <string>
#include <vector>

template <typename T>
std::string join(const std::vector<T>& in, const std::string& sep)
{
	std::ostringstream stream;
	for (int i = 0; i < in.size(); i++)
	{
		if (i) stream << sep;
		stream << in[i];
	}
	return stream.str();
}

std::vector<std::string> split(const std::string& in, const char sep)
{
	std::vector<std::string> result;
	std::istringstream ss(in);
	std::string item;

	while (std::getline(ss, item, sep))
	{
		result.push_back(item);
	}

	return result;
}