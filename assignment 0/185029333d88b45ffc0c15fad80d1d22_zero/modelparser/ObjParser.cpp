#include "ObjParser.h"
#include <iostream>
#include <sstream>

void ObjParser::read_file(std::ifstream& file, std::vector<Vector3f>& vertices, std::vector<Vector3f>& normals)
{
	if(!file.is_open()) return;

	std::string current_line{};
	while(std::getline(file, current_line))
	{
		auto type_to_vector = parse_string(current_line);
		if(type_to_vector.first == "v")
		{
			vertices.push_back(type_to_vector.second);
		}else if(type_to_vector.first == "vn")
		{
			normals.push_back(type_to_vector.second);
		}
		else
		{
			std::cout << current_line << "\n";
		}
	}
}

std::pair<std::string, Vector3f> ObjParser::parse_string(const std::string& line)
{
	std::stringstream string_stream{line};
	std::string line_type;
	string_stream >> line_type;
	Vector3f result{};
	if(line_type == "v" || line_type == "vn")
	{
		string_stream >> result[0] >> result[1] >> result[2];
	}else
	{
		return {};
	}
	
	return {line_type, result};
}
