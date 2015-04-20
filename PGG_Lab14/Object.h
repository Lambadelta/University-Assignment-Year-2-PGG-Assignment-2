#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include <glm.hpp>
#include "FaceVertex.h"
struct Object 
{
	std::vector<float> Verts;
	std::vector<float> Normals;
};

#endif