// Entry point
 
#include "math3d.hpp"

static void RunChallenge(const utils::Vector3& direction = utils::Vector3(0.0f))
{
	// Data sets
	std::vector<utils::Vertex> dataA, dataB;
	if (direction == utils::Vector3(0.0f))
	{
		math3d::LoadVertexFile("../resources/points_normals_0.txt", dataA);
		math3d::LoadVertexFile("../resources/points_normals_1.txt", dataB);
	}
	else
	{
		math3d::LoadVertexFile("../resources/points_normals_0.txt", dataA, direction);
		math3d::LoadVertexFile("../resources/points_normals_1.txt", dataB, direction);
	}

	if (dataA.size() <= 1)
	{
		utils::Print("DataA size too short! Maybe try another direction?", false);
		utils::Print("Dataset size: " + std::to_string(dataA.size()), true);
		return;
	}
	else if (dataB.size() <= 1)
	{
		utils::Print("DataB size too short! Maybe try another direction?", false);
		utils::Print("Dataset size: " + std::to_string(dataB.size()), true);
		return;
	}

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

	// 3.a Remove unused points
	std::vector<utils::Vertex> dataB2; // unused points
	math3d::RemoveUnusedPoints(dataB, distPairs, dataB2);
	utils::Print("3.a Unused points", false);
	utils::Print("Unused points count: " + std::to_string(dataB2.size()), true);

	// Extra: Memory data
	int size_dataA = (dataA.capacity() * sizeof(utils::Vertex)) / 1024;
	int size_dataB = (dataB.capacity() * sizeof(utils::Vertex)) / 1024;
	int size_distPairs = (distPairs.capacity() * sizeof(utils::VectorsDistance)) / 1024;
	int size_dataB2 = (dataB2.capacity() * sizeof(utils::Vertex)) / 1024;

	std::cout << "DataA size in memory (kb): " << size_dataA << "\n";
	std::cout << "DataB size in memory (kb): " << size_dataB << "\n";
	std::cout << "Distance pairs size in memory (kb): " << size_distPairs << "\n";
	std::cout << "DataB2 size in memory (kb): " << size_dataB2 << "\n\n";
}

int main()
{
	utils::Print("//\n// WITHOUT DIRECTION\n//", true);
	RunChallenge();

	// 4 Angled search
	utils::Print("//\n// WITH DIRECTION OF Vector3(0.384101f, 0.176491f, -0.906266f)\n//", true);
	RunChallenge(utils::Vector3(0.384101f, 0.176491f, -0.906266f));

	return 0;
}