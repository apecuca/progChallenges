#pragma once

// Std
#include <iostream>

namespace utils
{

	class Vector3
	{
	public:
		// Default constructor
		Vector3()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		};

		// All-round constructor
		Vector3(float vl)
		{
			x = vl;
			y = vl;
			z = vl;
		};

		// Parameter constructor
		Vector3(float _x, float _y, float _z)
		{
			x = _x;
			y = _y;
			z = _z;
		};

		// Copy constructor
		Vector3(const Vector3& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}

		// Values
		float x, y, z;

		// Functions
		static float Distance(const Vector3& a, const Vector3& b)
		{
			float d = ((b.x - a.x) * (b.x - a.x));
			d += ((b.y - a.y) * (b.y - a.y));
			d += ((b.z - a.z) * (b.z - a.z));
			d = std::sqrt(d);

			return d;
		}

	}; // Vector3

	class Vertex
	{
	public:
		// Base constructor
		Vertex()
		{
			point = Vector3(0.0f);
			normal = Vector3(0.0f);
		};

		// Copy constructor
		Vertex(const Vector3& _point, const Vector3& _normal)
		{
			point = _point;
			normal = _normal;
		};

		// Values
		Vector3 point;
		Vector3 normal;

	}; // Vertex

	class BoundingBox
	{
	public:
		// Default constructor
		BoundingBox()
		{
			min = Vector3();
			max = Vector3();
		}

		// Parameter constructor
		BoundingBox(const Vector3& _min, const Vector3& _max)
		{
			min = _min;
			max = _max;
		}

		// Values
		Vector3 min, max;

	}; // Bounding box

	class VectorsDistance
	{
	public:
		// Base constructor
		VectorsDistance()
		{
			pointA = Vector3();
			pointB = Vector3();
			indexA = 0;
			indexB = 0;
			distance = std::numeric_limits<float>::infinity();
		}

		// Value constructor
		VectorsDistance(const Vector3& pA, const Vector3& pB, 
			const int& iA, const int& iB, const float& dist)
		{
			pointA = pA;
			pointB = pB;
			indexA = iA;
			indexB = iB;
			distance = dist;
		}

		// Copy constructor
		VectorsDistance(const VectorsDistance& other)
		{
			pointA = other.pointA;
			pointB = other.pointB;
			indexA = other.indexA;
			indexB = other.indexB;
			distance = other.distance;
		}

		// Values
		Vector3 pointA, pointB;
		int indexA, indexB;
		float distance;
	}; // Vector distance

	static void Print(const Vector3& vector, bool doubleBrake)
	{
		std::cout << "Vector3(" << vector.x << ", " << vector.y << ", " << vector.z << ")\n";
		if (doubleBrake) std::cout << "\n";
	} // Print VECTOR

	static void Print(const BoundingBox& boundbox, bool doubleBrake)
	{
		std::cout << "Min: ";
		Print(boundbox.min, false);
		std::cout << "Max: ";
		Print(boundbox.max, doubleBrake);
	} // Print BOUNDING BOX

	static void Print(const Vertex& vertex, bool doubleBrake)
	{
		std::cout << "Point: " << vertex.point.x << ", " << vertex.point.y << ", " << vertex.point.z << "\n";
		std::cout << "Normal: " << vertex.normal.x << ", " << vertex.normal.y << ", " << vertex.normal.z << "\n";
		if (doubleBrake) std::cout << "\n";
	} // Print VERTEX

	static void Print(const std::string& text, bool doubleBrake)
	{
		std::cout << text << "\n";
		if (doubleBrake) std::cout << "\n";
	} // Print STRING

	/* EXAMPLE TO COPY
	static void Print(const TYPE& name, bool doubleBrake)
	{

	} // Print TYPE
	*/

} // namespace