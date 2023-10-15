#ifndef MODELPARSER_H
#define MODELPARSER_H

#include <string>
#include <vector>
#include <fstream>
#include "Vector3f.h"

class ModelParser
{
public:
	ModelParser() = default;
	ModelParser(const ModelParser&) = default;
	ModelParser(ModelParser&&) noexcept = default;
	ModelParser& operator=(const ModelParser&) = default;
	ModelParser& operator=(ModelParser&&) noexcept = default;
	virtual ~ModelParser() = default;

	virtual std::ifstream open_file(const std::string& filepath);
	virtual void read_file(const std::string& filepath, std::vector<Vector3f>& vertex_buffer, std::vector<Vector3f>& normals, std::vector<std::
	                       vector<unsigned>> index_buffer);
	virtual void read_file(std::ifstream& file, std::vector<Vector3f>& vertices, std::vector<Vector3f>& normals, std::vector<std::vector<unsigned>> index_buffer) = 0;
};

#endif
