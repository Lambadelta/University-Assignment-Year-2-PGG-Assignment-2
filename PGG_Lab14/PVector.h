#ifndef PVECTOR_H
#define PVECTOR_H

#include <cmath>
#include <math.h>
#include <ctime>
#include <cstdlib>
/************************************************************************/
/* Was submitted as part of AI Assignment 1                             */
/************************************************************************/

struct PVector
{
	float x;
	float y;
	float z;



	PVector()
	{
		x  = 0;
		y  = 0;
		z  = 0;
	};
	PVector(float xin, float yin)
	{
		x = xin;
		y = yin;
	};
	PVector(float xin, float yin, float zin)
	{
		x = xin;
		y = yin;
		z = zin;
	};
	PVector(PVector PV1, PVector PV2)
	{
		x = PV1.x - PV2.x;
		y = PV1.y - PV2.y;
		z = PV1.z - PV2.z;
	}
	void add(float xin, float yin, float zin)
	{
		x += xin;
		y += yin;
		z += zin;
	};
	void add(PVector PVin)
	{
		x += PVin.x;
		y += PVin.y;
		z += PVin.z;
	};
	void  sub(float xin, float yin, float zin)
	{
		x -= xin;
		y -= yin;
		z -= zin;
	};
	void sub(PVector PVin)
	{
		x -= PVin.x;
		y -= PVin.y;
		z -= PVin.z;
	};
	void sub(PVector PV1, PVector PV2)
	{
		x = PV1.x -= PV2.x;
		y = PV1.y -= PV2.y;
		z = PV1.z -= PV2.z;
	};
	void multiply(float n)
	{
		x *= n;
		y *= n;
		z *= n;
	};
	void  multiply(PVector PVin, float n)
	{
		PVin.x *= n;
		PVin.y *= n;
		PVin.z *= n;
	};
	void multiply(PVector PV1, PVector PV2)
	{
		PV1.x *= PV2.x;
		PV1.y *= PV2.y;
		PV1.z *= PV2.z;
	};
	void Divide(float n)
	{
		x /= n;
		y /= n;
		z /= n;
	};
	void  Divide(PVector PVin, float n)
	{
		PVin.x /= n;
		PVin.y /= n;
		PVin.z /= n;
	};
	void Divide(PVector PV1, PVector PV2)
	{
		PV1.x /= PV2.x;
		PV1.y /= PV2.y;
		PV1.z /= PV2.z;
	};
	void  Divide(PVector PV1, float n, PVector PV2)
	{
		PV1.x /= n;
		PV1.y /= n;
		PV1.z /= n;
		PV2 = PV1;
	};
	void  dot(PVector PV1, PVector PV2)
	{
		x += PV1.x*PV2.x;
		y += PV1.y*PV2.y;
		z += PV1.z*PV2.z;
	};
	void  setMag(float len)
	{
		float unitlen = Normalize();

		x *= len;
		y *= len;
		z *= len;
	}
	float Mag()
	{
		return (float)sqrt((x*x) + (y*y) + (z*z));
	};
	float Normalize()
	{
		float magnitude = Mag();

		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		return x + y + z;

	};
	void  random2D()
	{
		x = random(std::rand());
		y = random(std::rand());
		z = random(std::rand());
	}
	
	static float random(float seed)
	{
		std::srand(seed);
		return (float)std::rand();
	}
	static float dist(PVector PV1, PVector PV2)
	{
		float x = PV2.x - PV1.x;
		float y = PV2.y - PV1.y;
		float distance;

		distance = pow(x, 2) + (y, 2);
		distance = sqrt(distance);
		return distance;

	};
	void  limit(float n)
	{
		x /= n;
		y /= n;
		z /= n;
	}
	float Heading()
	{
		float result = atan2(y, x) * 180 / 3.14159265358979323846;
		return result;
	}
	static float radians(float n)
	{
		float result = n * 3.14159265358979323846 / 180;
		return result;
	}
};



#endif