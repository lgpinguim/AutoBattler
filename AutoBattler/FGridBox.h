#pragma once

// FGridBox represents a single tile or cell in the grid.
class FGridBox
{
public:
	int XIndex = 0;
	int YIndex = 0;
	bool bOccupied = false;
	int Index = 0;

	// Constructors
	FGridBox(const int InX, const int InY, const int InIndex) : XIndex(InX), YIndex(InY), Index(InIndex) {}
	FGridBox() = default;
};
