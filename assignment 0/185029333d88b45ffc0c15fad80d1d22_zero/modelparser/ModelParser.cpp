#include "ModelParser.h"

std::ifstream ModelParser::open_file(const std::string& filepath)
{
	return std::ifstream(filepath);
}

void ModelParser::read_file(const std::string& filepath, std::vector<Vector3f>& vertex_buffer,
                            std::vector<Vector3f>& normals, std::vector<std::vector<unsigned>> index_buffer)
{
	read_file(open_file(filepath), vertex_buffer, normals, index_buffer);
}
