#ifndef LOADER_H
#define LOADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <glm.hpp>
#include "FaceVertex.h"
#include "Object.h"
/**
@brief A class representing a Object Loader
*/
class Loader
{
public:

	/**
	@brief A Method that Loads in an Obj File
	@param std::string - A string containing path
	*/
	void Load(std::string objFileName);
	/**
	@brief A Method that Reads an Obj File
	@param File* - A file pointer
	*/
	void ReadObjFileData(FILE* objFile);
	/**
	@brief A Method that loads, and reads in an Obj File
	This is currently broken
	@param std::string - A string containing path
	@returns bool - If it was a success or failure
	*/
	bool objLoader(std::string);
	/**
	@brief A Method that is used to Extract Face data from the file
	@param std::string - A reference to a string containing the data to extract
	@return FaceVertex - A structure containing all the datas
	*/
	FaceVertex ExtractFaceVertexData(std::string&);
	/**
	@brief A Method that Builds the std::vector<float> up using the Face data
	*/
	void BuildMeshVertAndNormalLists();
	/**
	@brief A Method that calls all the functions needed, and returns all the data in a neat Object format.
	@param std:;string a string containing path
	@returns Object - The Obj file converted into an Object file
	*/
	Object packageModelObject(std::string);
	/**
	@brief A Method that clears previously loaded data to allow the Loader to load new models.
	*/
	void clearLoadedData();


	

private:
	///A vector for vertices
	std::vector<glm::vec3>  Verts;
	///A vector for texture coordinates
	std::vector<glm::vec2>  UV;
	///A vector for normals
	std::vector<glm::vec3>  Normals;
	///A vector for face vertexs
	std::vector<FaceVertex> FVerts;

	///Finalized data vertices
	std::vector<float> mVerts;
	///Finalized data normals
	std::vector<float> mNormals;
	///Finalized data tex coordinates
	std::vector<float> mTexCoord;

};

#endif