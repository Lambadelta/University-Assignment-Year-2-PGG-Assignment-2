#include "Loader.h"

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
void Loader::BuildMeshVertAndNormalLists() {

	for (int i = 0; i < FVerts.size(); i++) {
		//the ith vnp in the std::vector
		FaceVertex* vnp = &FVerts[i];

		//pack ith vnp's vertex data into the meshVertices list
		if (vnp->Vertex > 0) {
			mVerts.push_back(Verts[vnp->Vertex - 1].x);
			mVerts.push_back(Verts[vnp->Vertex - 1].y);
			mVerts.push_back(Verts[vnp->Vertex - 1].z);
		}

		//pack ith vnp's normal data into the meshVertices list
		if (vnp->Normal > 0) {
			mNormals.push_back(Verts[vnp->Normal - 1].x);
			mNormals.push_back(Verts[vnp->Normal - 1].y);
			mNormals.push_back(Verts[vnp->Normal - 1].z);
		}
		else {
			/* if a vertex had no corresponding normal, like say if
			* there was a line like "f 12 45 89 34" then we add
			* a normal of (1,0,0) just to stop OpenGL moaning.
			* There are better ways to go about this though. */
			mNormals.push_back(1);
			mNormals.push_back(0);
			mNormals.push_back(0);
		}
	}
}
FaceVertex Loader::ExtractFaceVertexData(std::string& s) {

	//we will see how many '/' the above string contains, and store their positions
	int slashPos[2];
	int slashCount = 0;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '/') {
			slashPos[slashCount] = i;
			slashCount++;
		}
	}

	/* this struct will hold whatever information we are
	* able to obtain about the face vertex. This will be
	* a combination of vertex, tex-coord and normal ids */
	FaceVertex result;

	if (slashCount == 0) {
		/* if we found no slashes then we probably have just a
		* vertex id so just convert to an int and store it */

		result.Vertex = std::stoi(s); //convert the whole of string s into an int
	}
	else if (slashCount == 1) {
		/* if we found one slash then we have just a vertex id
		* and normal id. Split the string into these two sub-
		* strings and convert them to ints. Store as necessary */

		result.Vertex = std::stoi(s.substr(0, slashPos[0]));	//convert up to the '/' into an int
		result.Normal = std::stoi(s.substr(slashPos[0] + 1));   //convert everything after the '/' to an int
	}
	else if (slashCount == 2) {
		/* if we have found two '/'s then it's slightly more
		* complicated as we could either have something like
		* "1/2/3" or "1//2". Extracting the vertex and normal
		* is the same in either case: */

		result.Vertex = std::stoi(s.substr(0, slashPos[0]));  //convert up to the first '/' into an int
		result.Normal = std::stoi(s.substr(slashPos[1] + 1)); //convert everything after the second '/' to an int

		/* for the tex-coord, we will grab a sub-string of between
		* the two '/'s, if that string is 0 length then we do not
		* need to do anything, but if not then we need to turn
		* whatever we have into an int, this is the tex-coord id */

		std::string texCoordString = s.substr(slashPos[0] + 1, (slashPos[1] - (slashPos[0])) - 1);
		if (texCoordString.size() > 0)
			result.TexCoordinate = std::stoi(texCoordString);

	}

	return result;
}