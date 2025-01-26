// Entry point
 
#include "math3d.hpp"

int main()
{
	// Data sets
	std::vector<utils::Vertex> dataA, dataB;
	math3d::LoadVertexFile("../resources/points_normals_0.txt", dataA);
	math3d::LoadVertexFile("../resources/points_normals_1.txt", dataB);
	
	// 1 Calculate bounding boxes
	utils::BoundingBox bbA = math3d::CalculateBoundingBox(dataA);
	utils::BoundingBox bbB = math3d::CalculateBoundingBox(dataB);

	// 1.a Print bounding boxes
	utils::Print("1.a Bounding boxes", false);
	utils::Print("DataA: ", false);
	utils::Print(bbA, true);
	utils::Print("DataB: ", false);
	utils::Print(bbB, true);

	// 1.b Calculate intersection volume
	std::string intersecVol = math3d::CalculateIntersectionVol(bbA, bbB);
	utils::Print("1.b Inserction volume between dataA and dataB: \n" + intersecVol, true);

	// 2 Distance pairs
	std::vector<utils::VectorsDistance> distPairs;
	math3d::FindClosestPairs(dataA, dataB, distPairs);

	// 2.a Closest pairs
	utils::VectorsDistance closestPair = math3d::FindClosestPair(distPairs);
	utils::Print("2.a Closest pair ", false);
	utils::Print("Distance: " + std::to_string(closestPair.distance), false);
	utils::Print(closestPair.pointA, false);
	utils::Print("Point A index on dataA dataset: " + std::to_string(closestPair.indexA), false);
	utils::Print(closestPair.pointB, false);
	utils::Print("Point B index on dataB dataset: " + std::to_string(closestPair.indexB), true);

	return 0;
}