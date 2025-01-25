#pragma once

// Standard
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

// Classes
#include "utils.hpp"

namespace math3d
{
	
	std::vector<utils::Vertex> LoadVertexFile(const char* filePath)
	{
		std::ifstream file(filePath);

		// Reading vars
		std::vector<float> points;
		std::string line;
		std::string numberCell;

		// Ready every line inside the file
		while (std::getline(file, line))
		{
			// Pass the result of the line to a stringstream
			std::stringstream ss(line);

			// Read the line separated into cells, divided by a comma
			while (std::getline(ss, numberCell, ',')) {
				// Parse and push the cells to a point 
				points.push_back(std::stof(numberCell));
			}
		}

		//
		// I COULD do the following code inside the reading loop,
		// but it would be too cramped and hard to read
		//

		// Create array to store vertex data and
		// reserve space to minimize copies
		std::vector<utils::Vertex> vertexData;
		vertexData.reserve((points.size() / 3) / 2);

		// Temp data for loop
		int loopSteps = 0;
		utils::Vector3 tempPoint = utils::Vector3(0.0f);
		utils::Vector3 tempNormal = utils::Vector3(0.0f);

		for (int i = 0; i < points.size(); i++)
		{
			// Easier to read than a switch.
			// Since the array containing the values is sequencial,
			// the order will ALWAYS be this, as long as the file
			// is in the correct format (and they are)
			if (loopSteps == 0) tempPoint.x = points[i];
			else if (loopSteps == 1) tempPoint.y = points[i];
			else if (loopSteps == 2) tempPoint.z = points[i];
			else if (loopSteps == 3) tempNormal.x = points[i];
			else if (loopSteps == 4) tempNormal.y = points[i];
			else if (loopSteps == 5) tempNormal.z = points[i];

			loopSteps++;
			if (loopSteps == 6)
			{
				// emplace new vertex with current data
				vertexData.emplace_back(tempPoint, tempNormal);
				loopSteps = 0;
			}
		}

		return vertexData;
	} // Load vertex file

	utils::BoundingBox CalculateBoundingBox(const std::vector<utils::Vertex>& data)
	{
		// Temp min and max points
		utils::Vector3 min = utils::Vector3(data.at(0).point);
		utils::Vector3 max = utils::Vector3(data.at(0).point);

		// Save min and max points
		for (int i = 0; i < data.size(); i++)
		{
			if (data.at(i).point.x < min.x) min.x = data.at(i).point.x;
			if (data.at(i).point.y < min.y) min.y = data.at(i).point.y;
			if (data.at(i).point.z < min.z) min.z = data.at(i).point.z;
			if (data.at(i).point.x > max.x) max.x = data.at(i).point.x;
			if (data.at(i).point.y > max.y) max.y = data.at(i).point.y;
			if (data.at(i).point.z > max.z) max.z = data.at(i).point.z;
		}

		// Allocate and return bounds
		utils::BoundingBox bounds = utils::BoundingBox(min, max);

		return bounds;
	} // Calculate bounding box

	std::string CalculateIntersectionVol(const utils::BoundingBox& a, const utils::BoundingBox& b)
	{
		// Clamping to 0 the subtraction of the min and max possible values
		// This gives us the overlapping between two points in one dimension
		double x_overlap = std::max(0.0f, std::min(a.max.x, b.max.x) - std::max(a.min.x, b.min.x));
		double y_overlap = std::max(0.0f, std::min(a.max.y, b.max.y) - std::max(a.min.y, b.min.y));
		double z_overlap = std::max(0.0f, std::min(a.max.z, b.max.z) - std::max(a.min.z, b.min.z));

		// Then, calculate the volume by multiplying the 3 dimensions

		// Turning to string because the console doesn't want to
		// print a number this big, for some reason
		std::string intersecVol = std::to_string(x_overlap * y_overlap * z_overlap);
		// In square meters because it's fancyyyyy
		intersecVol += "m2";

		return intersecVol;
	}

}; // Namespace