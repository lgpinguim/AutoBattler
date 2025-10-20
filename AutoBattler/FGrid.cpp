#include "FGrid.h"

FGrid::FGrid(int& InLines, int& InColumns) : XLength(InLines), YLength(InColumns)
{
    for (int X = 0; X < XLength; ++X)
    {
        for (int Y = 0; Y < YLength; ++Y)
        {
            GridBoxes.emplace_back(Y, X, InColumns * X + Y);
        }
    }
}
