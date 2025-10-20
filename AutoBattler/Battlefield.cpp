#include "FGrid.h"
#include "FBattlefield.h"
#include "FGridBox.h"
#include "FCharacterBase.h"
#include <iostream>
#include "FRandomUtils.h"

using namespace std;

FBattlefield::FBattlefield()= default;

void FBattlefield::SetGrid(FGrid* NewGrid)
{
    GridRef = NewGrid;
}

FGrid* FBattlefield::CreateBattlefield(int& Lines, int& Columns)
{
    FGrid* NewGrid = new FGrid(Lines, Columns);
    cout << "\nThe battlefield has been created\n";
    SetGrid(NewGrid);

    NumPossibleTiles = NewGrid->XLength * NewGrid->YLength;
    return NewGrid;
}

void FBattlefield::AllocatePlayer(FCharacterBase* Player)
{
    bool bSearchingValidPosition = true;

    while (bSearchingValidPosition)
    {
        const int Random = FRandomUtils::GetRandomInt(0, NumPossibleTiles - 1);
        auto FrontIterator = GridRef->GridBoxes.begin();
        advance(FrontIterator, Random);

        const FGridBox* RandomLocation = &*FrontIterator;

        if (!RandomLocation->bOccupied)
        {
            PlayerIndexLocations.push_back(FrontIterator->Index);
            FrontIterator->bOccupied = true;
            Player->CurrentBox = *FrontIterator;
            bSearchingValidPosition = false;
        }
    }
}

void FBattlefield::ValidateBattlefieldDimensions(int& Lines, int& Columns) const
{
    bool bIncorrectInput = true;

    while (bIncorrectInput)
    {
        cout << "\nPlease choose the map height: ";
        string Height;
        getline(cin, Height);

        cout << "Please choose the map width: ";
        string Width;
        getline(cin, Width);

        Lines = atoi(Height.c_str());
        Columns = atoi(Width.c_str());

        const bool bIsValidMatrixSize = Lines * Columns >= 2;

        if (bIsValidMatrixSize)
        {
            bIncorrectInput = false;
        }
        else
        {
            cout << "Wrong dimensions, please try again!\n";
        }
    }
}

void FBattlefield::DrawBattlefield(const vector<FCharacterBase*>& AllPlayers) const
{
    int Index = 0;

    for (int i = 0; i < GridRef->XLength; i++)
    {
        for (int j = 0; j < GridRef->YLength; j++)
        {
            const FGridBox CurrentGrid = GridRef->GridBoxes[Index];

            if (CurrentGrid.bOccupied)
            {
                for (const FCharacterBase* Player : AllPlayers)
                {
                    if (Player->CurrentBox.Index == CurrentGrid.Index)
                    {
                        cout << "[" << Player->Icon << "]\t";
                    }
                }
            }
            else
            {
                cout << "[ ]\t";
            }

            Index++;
        }

        printf("\n");
    }

    printf("\n");
}
