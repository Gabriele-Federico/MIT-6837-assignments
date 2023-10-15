#include "ObjParser.h"
#include <iostream>
#include <sstream>

void ObjParser::read_file(std::ifstream& file, std::vector<Vector3f>& vertices, std::vector<Vector3f>& normals, std::vector<std::vector<unsigned>
                          >)
{
	if(!file.is_open()) return;

	std::string current_line{};
	while(std::getline(file, current_line))
	{
		std::stringstream string_stream{current_line};
		std::string type_string;
		string_stream >> type_string;
		const data_type type = get_type(type_string);
		switch (type)
		{
		case data_type::vertex:
		{
			Vector3f vertex;
			string_stream >> vertex[0] >> vertex[1] >> vertex[2];
			vertices.push_back(vertex);
			break;
		}
		case data_type::normal:
		{
			Vector3f normal;
			string_stream >> normal[0] >> normal[1] >> normal[2];
			normals.push_back(normal);
			break;
		}
		case data_type::face:
		{
			std::cout << current_line << "\n";
			break;
		}
		default:
			break;
		}
		
	}
}

ObjParser::data_type ObjParser::get_type(const std::string& type_string)
{
	if (type_string == "v")
	{
		return data_type::vertex;
	}
	if (type_string == "vn")
	{
		return data_type::normal;
	}
	if (type_string == "f")
	{
		return data_type::face;
	}
	return data_type::none;
}

