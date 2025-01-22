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

	void PrintVector(const Vector3& vector, bool doubleBrake)
	{
		std::cout << "Vector3(" << vector.x << ", " << vector.y << ", " << vector.z << ")\n";
		if (doubleBrake) std::cout << "\n";
	} // Print vector

	void PrintVertex(const Vertex& vertex, bool doubleBrake)
	{
		std::cout << "Point: " << vertex.point.x << ", " << vertex.point.y << ", " << vertex.point.z << "\n";
		std::cout << "Normal: " << vertex.normal.x << ", " << vertex.normal.y << ", " << vertex.normal.z << "\n";
		if (doubleBrake) std::cout << "\n";
	} // print vertex

	void PrintBoundingBox(const BoundingBox& boundbox, bool doubleBrake)
	{
		std::cout << "Min: ";
		PrintVector(boundbox.min, false);
		std::cout << "Max ";
		PrintVector(boundbox.max, doubleBrake);
	} // Print bounding box

} // namespace