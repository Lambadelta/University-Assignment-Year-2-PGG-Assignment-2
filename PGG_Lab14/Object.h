#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <glm.hpp>
#include "FaceVertex.h"
/**
@brief A struct representing an Object

Contains 3 vectors that make up a Obj file.
*/
struct Object 
{
	std::vector<float> Verts;
	std::vector<float> Normals;
	std::vector<float> texCoord;
	Object()
	{

	}
	Object(std::vector<float> Vin, std::vector<float> Nin)
	{
		Verts = Vin;
		Normals = Nin;
	}
	Object(std::vector<float> Vin, std::vector<float> Nin, std::vector<float> TCin)
	{
		Verts = Vin;
		Normals = Nin;
		texCoord = TCin;
	}
};

#endif