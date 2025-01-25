// Entry point
 
#include "3d_math.hpp"

int main()
{
	// Data sets
	std::vector<utils::Vertex> dataA = math3d::LoadVertexFile("../resources/points_normals_0.txt");
	std::vector<utils::Vertex> dataB = math3d::LoadVertexFile("../resources/points_normals_1.txt");
	
	// 1 Calculate bounding boxes
	utils::BoundingBox bbA = math3d::CalculateBoundingBox(dataA);
	utils::BoundingBox bbB = math3d::CalculateBoundingBox(dataB);

	// 1.a Print bounding boxes
	utils::Print(bbA, true);
	utils::Print(bbB, true);

	// 1.b Calculate intersection volume
	std::string intersecVol = math3d::CalculateIntersectionVol(bbA, bbB);
	utils::Print(intersecVol, true);

	

	return 0;
}