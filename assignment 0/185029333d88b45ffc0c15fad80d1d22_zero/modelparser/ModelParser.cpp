#include "ModelParser.h"

std::ifstream ModelParser::open_file(const std::string& filepath)
{
	return std::ifstream(filepath);
}

void ModelParser::read_file(const std::string& filepath, std::vector<Vector3f>& vertices,
                            std::vector<Vector3f>& normals)
{
	read_file(open_file(filepath), vertices, normals);
}
