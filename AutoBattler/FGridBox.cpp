#include "FGridBox.h"

#include <vector>

class FGrid
{
public:
	FGrid(int& InLines, int& InColumns);

	std::vector<FGridBox> GridBoxes;
	int XLength = 0;
	int YLength = 0;
};
