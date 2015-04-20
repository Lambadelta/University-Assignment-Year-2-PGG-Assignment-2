#ifndef LOADER_H
#define LOADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "glm.hpp"
#include "FaceVertex.h"

class Loader
{
public:

	bool objLoader(std::string);
	FaceVertex ExtractFaceVertexData(std::string&);
	void BuildMeshVertAndNormalLists();
	std::vector<float>& getVerts(){ return mVerts; }
	std::vector<float>& getNormals(){ return mNormals; }

	

private:
	std::vector<glm::vec3> Verts;
	std::vector<glm::vec2> UV;
	std::vector<glm::vec3> Normals;
	std::vector<FaceVertex> FVerts;


	std::vector<float> mVerts;
	std::vector<float> mNormals;

};

#endif