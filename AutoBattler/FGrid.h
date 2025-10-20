#pragma once

#include <vector>

#include "FGridBox.h"

class FGrid
{
public:
	// Constructor
	FGrid(int& InLines, int& InColumns);

	// Member variables
	std::vector<FGridBox> GridBoxes;
	int XLength = 0;
	int YLength = 0;
};
