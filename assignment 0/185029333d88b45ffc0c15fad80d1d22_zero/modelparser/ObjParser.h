#ifndef OBJPARSER_H
#define OBJPARSER_H

#include "ModelParser.h"

class ObjParser : public ModelParser
{
public:
	ObjParser() = default;
	ObjParser(const ObjParser&) = default;
	ObjParser(ObjParser&&) noexcept = default;
	ObjParser& operator=(const ObjParser&) = default;
	ObjParser& operator=(ObjParser&&) noexcept = default;
	void read_file(const std::ifstream& file, std::vector<Vector3f>& vertices, std::vector<Vector3f>& normals) override;
};

#endif
