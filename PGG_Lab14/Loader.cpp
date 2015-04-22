#include "Loader.h"
void Loader::Load(std::string objFileName) {

	FILE * objFile;

	fopen_s(&objFile, objFileName.c_str(), "r");

	if (NULL == objFile)
		printf("Could not open obj file: %s\n", objFileName);

	//rips the raw data out of the obj file and stores it in various std::vectors
	ReadObjFileData(objFile);

	//builds vertex and normal std::vectors based on the above
	BuildMeshVertAndNormalLists();

	fclose(objFile);
}
void Loader::ReadObjFileData(FILE* objFile) {

	char buffer[256];

	while (true) {

		int read = fscanf_s(objFile, "%s", buffer, sizeof(buffer));
		if (read == EOF) break;

		//if first part of the line is "v"
		if (strcmp(buffer, "v") == 0) {
			//printf("Found a Vertex:\n");
			glm::vec3 vert;
			fscanf_s(objFile, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
			Verts.push_back(vert);
		}

		//if first part of the line is "vn"
		else if (strcmp(buffer, "vn") == 0) {
			//printf("Found a Vertex Normal:\n");
			glm::vec3 normal;
			fscanf_s(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			Normals.push_back(normal);
		}

		//if first part of the line is "f"
		else if (strcmp(buffer, "f") == 0) {
			//printf("Found f:\n");

			/* we need to split the line following 'f' into individual bits
			* for processing i.e "1/2/3", "2/1/3", "3/3/3" etc
			*
			* NOTE - There's probably a more efficient way than this! */

			//read the line, turn it into a std::string and put that in a stringstream
			fscanf_s(objFile, "%256[^\n]", buffer, sizeof(buffer));
			std::string s(buffer);
			std::stringstream stream(s);

			/* find each "word" in the stringstream (i.e. something like "1/2/3"
			* and store it as 'split', also add each split to the 'splits' std::vec */
			std::string split;
			std::vector<std::string> splits;
			while (stream >> split)
				splits.push_back(split);

			/* now just send each split to the function which works out what they contain
			* and store what comes back in the faceVerts std::vector */
			for (int i = 0; i < splits.size(); i++)
				FVerts.push_back(ExtractFaceVertexData(splits[i]));
		}
		else {
			printf("> Found unrecognised obj line: %s\n", buffer);
		}
	}
}
bool Loader::objLoader(std::string path)
{
	std::ifstream in(path, std::ios::in);
	if (!in) 
	{
		std::printf("%c", "Error : OBJ File failed to load.");
		return false;
	}
	std::string linein;
	while (std::getline(in, linein))
	{
		std::istringstream ss (linein);
		std::string type;
		ss >> type;
		
		if (type == "v")
		{
			//vertex
			float x = 0, y = 0, z = 0;
			ss >> x >> y >> z;
			Verts.push_back(glm::vec3(x, y, z));
		}

		if (type == "vt")
		{
			//texture
			float u = 0, v = 0;
			ss >> u >> v;
			UV.push_back(glm::vec2(u, v));
		}
		if (type == "vn")
		{
			//Normals
			float i = 0, j = 0, k = 0;

			ss >> i >> j >> k;
			Normals.push_back(glm::vec3(i, j, k));
		}
		if (type == "f")
		{
			//faces
			std::string split;
			std::vector<std::string> vSplit;
			ss >> split;
			vSplit.push_back(split);
			for (int i = 0; i < vSplit.size(); i++)
			{
				FVerts.push_back(ExtractFaceVertexData(vSplit[i]));
			}
		}

		if (type == "#")
		{
			//ignore this line
		}
	}
	return true;
}
void Loader::BuildMeshVertAndNormalLists() 
{
	for (int i = 0; i < FVerts.size(); i++)
	{
		FaceVertex* vnp = &FVerts[i];
		if (vnp->Vertex > 0)
		{
			mVerts.push_back(Verts[vnp->Vertex - 1].x);
			mVerts.push_back(Verts[vnp->Vertex - 1].y);
			mVerts.push_back(Verts[vnp->Vertex - 1].z);
		}
		if (vnp->Normal > 0) 
		{
			mNormals.push_back(Normals[vnp->Normal - 1].x);
			mNormals.push_back(Normals[vnp->Normal - 1].y);
			mNormals.push_back(Normals[vnp->Normal - 1].z);
		}
		else 
		{
			mNormals.push_back(1);
			mNormals.push_back(0);
			mNormals.push_back(0);
		}
	}
}

Object Loader::packageModelObject(std::string PATH)
{
	Load(PATH);
	//objLoader(PATH);
	//BuildMeshVertAndNormalLists();
	Object Package(mVerts, mNormals);

	return Package;
}

FaceVertex Loader::ExtractFaceVertexData(std::string& s) {

	//we will see how many '/' the above string contains, and store their positions
	int slashPos[2];
	int slashCount = 0;

	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '/') 
		{
			slashPos[slashCount] = i;
			slashCount++;
		}
	}

	FaceVertex result;

	if (slashCount == 0) 
	{
		result.Vertex = std::stoi(s); //convert the whole of string into an int
	}
	else if (slashCount == 1) 
	{
		result.Vertex = std::stoi(s.substr(0, slashPos[0]));	//convert up to the '/' into an int
		result.Normal = std::stoi(s.substr(slashPos[0] + 1));   //convert everything after the '/' to an int
	}
	else if (slashCount == 2)
	{
		result.Vertex = std::stoi(s.substr(0, slashPos[0]));  //convert up to the first '/' into an int
		result.Normal = std::stoi(s.substr(slashPos[1] + 1)); //convert everything after the second '/' to an int
		std::string texCoordString = s.substr(slashPos[0] + 1, (slashPos[1] - (slashPos[0])) - 1);
		if (texCoordString.size() > 0)
		{
			result.TexCoordinate = std::stoi(texCoordString);
		}

	}
	return result;
}