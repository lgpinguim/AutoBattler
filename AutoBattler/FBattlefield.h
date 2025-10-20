#pragma once

#include "FCharacterBase.h"
#include "FGrid.h"
#include <vector>

class FBattlefield
{
public:
    FBattlefield();

    // Members
    FGrid* GridRef = nullptr;
    std::vector<int> PlayerIndexLocations;
    int NumPossibleTiles = 0;

    // Methods
    void SetGrid(FGrid* InGrid);
    FGrid* CreateBattlefield(int& InLines, int& InColumns);
    void AllocatePlayer(FCharacterBase* InPlayer);
    void ValidateBattlefieldDimensions(int& InLines, int& InColumns) const;
    void DrawBattlefield(const std::vector<FCharacterBase*>& AllPlayers) const;
};
