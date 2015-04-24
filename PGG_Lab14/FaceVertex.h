#ifndef FACEVERTEX_H
#define FACEVERTEX_H
/**
@brief A struct containing the data that makes up a Face
*/
struct FaceVertex 
{
	int Vertex;
	int TexCoordinate;
	int Normal;

	FaceVertex()
	{
		Vertex = 0;
		TexCoordinate = 0;
		Normal = 0;
	}
};


#endif