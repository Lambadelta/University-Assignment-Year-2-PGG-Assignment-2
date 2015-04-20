#include "ObjLoader.h"
#include <sstream>

ObjLoader::ObjLoader() {

}

ObjLoader::~ObjLoader() {

}

void ObjLoader::Load(std::string objFileName) {
	
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

void ObjLoader::ReadObjFileData(FILE* objFile) {

	char buffer[256];

	while (true) {

		int read = fscanf_s(objFile, "%s", buffer, sizeof(buffer));
		if (read == EOF) break;

		//if first part of the line is "v"
		if (strcmp(buffer, "v") == 0) {
			//printf("Found a Vertex:\n");
			glm::vec3 vert;
			fscanf_s(objFile, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
			objFileVerts.push_back(vert);
		}

		//if first part of the line is "vn"
		else if (strcmp(buffer, "vn") == 0) {
			//printf("Found a Vertex Normal:\n");
			glm::vec3 normal;
			fscanf_s(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			objFileNormals.push_back(normal);
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
				faceVerts.push_back(ExtractFaceVertexData(splits[i]));
		}
		else {
			printf("> Found unrecognised obj line: %s\n", buffer);
		}
	}
}

/* This function is called once we have extracted everything from the 
 * obj file. It looks at all the 'face vertex' definitions (i.e "1/2/3")
 * and used them to build two std::vectors, one with all the right
 * vertex positions inside in the right order and another for the
 * normals. Tex-coord data is basically ignored.
 *
 * Two std::vectors can be used in a standard OpenGL glDrawArrays
 * procedure. This doesn't support anything clever like indexed 
 * draws (look up "index buffer rendering OpenGL")but that wouldn't 
 * be that hard to add on. */
void ObjLoader::BuildMeshVertAndNormalLists() {

	for (int i = 0; i < faceVerts.size(); i++) {
		//the ith vnp in the std::vector
		FaceVertexData* vnp = &faceVerts[i];
		
		//pack ith vnp's vertex data into the meshVertices list
		if (vnp->Vertex > 0) {
			meshVertices.push_back(objFileVerts[vnp->Vertex - 1].x);
			meshVertices.push_back(objFileVerts[vnp->Vertex - 1].y);
			meshVertices.push_back(objFileVerts[vnp->Vertex - 1].z);
		}

		//pack ith vnp's normal data into the meshVertices list
		if (vnp->Normal > 0) {
			meshNormals.push_back(objFileVerts[vnp->Normal - 1].x);
			meshNormals.push_back(objFileVerts[vnp->Normal - 1].y);
			meshNormals.push_back(objFileVerts[vnp->Normal - 1].z);
		}
		else {
			/* if a vertex had no corresponding normal, like say if
			 * there was a line like "f 12 45 89 34" then we add 
			 * a normal of (1,0,0) just to stop OpenGL moaning.
			 * There are better ways to go about this though. */
			meshNormals.push_back(1);
			meshNormals.push_back(0);
			meshNormals.push_back(0);
		}
	}
}

/*
 * This function receives a single portion of a 'f' line at a time
 * 
 * Examples:
 *
 *    "123"   - Just a vertex id
 *    "1/2"   - Vertex and normal ids
 *    "1//2"  - Again, vertex and normal ids
 *    "1/2/3" - Vertex, texture-coordinate and normal ids
 *
 * The job of this function is to work out what information it has been
 * passed, store it in a FaceVertexData struct and then return that to
 * the caller.
 */
FaceVertexData ObjLoader::ExtractFaceVertexData(std::string& s) {

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
	FaceVertexData result;

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
			result.TexCoord = std::stoi(texCoordString);
		
	}

	return result;
}