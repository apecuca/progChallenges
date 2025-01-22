// Entry point
 
#include "3d_math.hpp"

int main()
{
	std::vector<Vertex> dataA = math3d::LoadVertexFile("../resources/points_normals_0.txt");
	std::vector<Vertex> dataB = math3d::LoadVertexFile("../resources/points_normals_1.txt");
	
	BoundingBox bbA = math3d::CalculateBoundingBox(dataA);
	BoundingBox bbB = math3d::CalculateBoundingBox(dataB);
	PrintBoundingBox(bbA, true);
	PrintBoundingBox(bbB, true);

	return 0;
}