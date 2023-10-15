#ifndef OBJPARSER_H
#define OBJPARSER_H

#include "ModelParser.h"

class ObjParser : public ModelParser
{
	enum class data_type
	{
		vertex,
		normal,
		face,
		none
	};
public:
	ObjParser() = default;
	ObjParser(const ObjParser&) = default;
	ObjParser(ObjParser&&) noexcept = default;
	ObjParser& operator=(const ObjParser&) = default;
	ObjParser& operator=(ObjParser&&) noexcept = default;

	void read_file(std::ifstream& file, std::vector<Vector3f>& vertices, std::vector<Vector3f>& normals, std::vector<std::vector<unsigned>>) override;
private:
	ObjParser::data_type get_type(const std::string& type_string);

};

#endif
