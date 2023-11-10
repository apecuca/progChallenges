// Marco Bossle Villanova
// /in/marco-bossle-villanova-02b321187/

#include "Interfaces.h"

// Main class that'll run all challenges
class EasyChallenges : public IMisc
{
public:
	void Start()
	{
		// CHALLENGE 01 - Absolute sum of integers
		print("CHALLENGE 01 - Absolute sum of integers", true);
		print("Return the absolute sum of numbers in given array", true);
		int arrSum[] = { 1, 3, -2, 3, 6 };
		print("Absolute sum of integers (1, 3, -2, 3, 6): ");
		print(getAbsSum(
			arrSum, sizeof(arrSum) / sizeof(int)), true);

		breakln();

		// CHALLENGE 02 - Is the bridge safe?
		print("CHALLENGE 02 - Broken bridge?", true);
		print("Check if the bridge is safe to walk on (no gaps to fall)", true);
		print("Is the bridge safe? (### ##): ");
		getIsBridgeSafe("### ##") ? print("Yes", true) : print("No", true);

		breakln();
	}

private:
	int getAbsSum(int _number[], int _arrSize)
	{
		// adition total
		int _total = 0;

		for (int i = 0; i < _arrSize; i++)
		{
			// abs returns the absolute value of parameter
			_total += abs(_number[i]);
		}

		// returns total
		return _total;
	}

	bool getIsBridgeSafe(string _bridge)
	{
		for (int i = 0; i < _bridge.length(); i++)
		{
			// Check if char is a bridge piece
			// If it isn't, it's not safe
			if (_bridge[i] != '#')
				return false;
		}

		return true;
	}
};


// yeah
int main()
{
	// Easy challenges to start learning and memorizing c++
	EasyChallenges easy;
	easy.Start();

	return 0;
}

