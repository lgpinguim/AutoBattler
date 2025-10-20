#include "FCharacterBase.h"
#include "FBattlefield.h"
#include "FGrid.h"
#include "FRandomUtils.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

FCharacterBase::FCharacterBase() = default;

int FCharacterBase::ValidateCreationInput() const
{
    cout << "Choose Between One of These Classes:\n";
    cout << "[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer\n";

    bool bNeedsChoice = true;
    int ClassIndex = 0;

    while (bNeedsChoice)
    {
        string Choice;
        getline(cin, Choice);
        ClassIndex = atoi(Choice.c_str());

        if (Choice.empty() || ClassIndex < 1 || ClassIndex > 4)
        {
            cout << "Invalid input, please try again:\n";
        }
        else
        {
            bNeedsChoice = false;
        }
    }

    return ClassIndex;
}

string FCharacterBase::CreateCharacterName() const
{
    string InputName;
    bool bNeedsName = true;

    cout << "\nCharacter name: ";

    while (bNeedsName)
    {
        getline(cin, InputName);

        if (InputName.empty())
        {
            cout << "\nInvalid name input, try again: ";
        }
        else
        {
            bNeedsName = false;
        }
    }

    return InputName;
}

void FCharacterBase::SetTarget(FCharacterBase* t)
{
	Target = t;
}

void FCharacterBase::TakeDamage(float& Amount)
{
    if ((Health -= Amount) <= 0)
    {
        Die();
    }
}

void FCharacterBase::Die()
{
    bIsDead = true;
    cout << Name << " is dead!\n";
}

bool FCharacterBase::CheckCloseTargets(FGrid* Battlefield) const
{
    int PlayerBoxIndex = CurrentBox.Index;

    const auto It = find_if(Battlefield->GridBoxes.begin(), Battlefield->GridBoxes.end(),
        [&PlayerBoxIndex](const FGridBox& GridBox)
        {
            return GridBox.bOccupied && GridBox.Index != PlayerBoxIndex;
        });

    if (It == Battlefield->GridBoxes.end())
        return false;

    return ((CurrentBox.XIndex - 1 == It->XIndex && CurrentBox.YIndex == It->YIndex)
        || (CurrentBox.XIndex + 1 == It->XIndex && CurrentBox.YIndex == It->YIndex)
        || (CurrentBox.XIndex == It->XIndex && CurrentBox.YIndex + 1 == It->YIndex)
        || (CurrentBox.XIndex == It->XIndex && CurrentBox.YIndex - 1 == It->YIndex));
}

void FCharacterBase::WalkLeft(FBattlefield* Battlefield, int& ListPosition)
{
    Move(Battlefield, -1, ListPosition, "left");
}

void FCharacterBase::WalkRight(FBattlefield* Battlefield, int& ListPosition)
{
    Move(Battlefield, 1, ListPosition, "right");
}

void FCharacterBase::WalkUp(FBattlefield* Battlefield, int& ListPosition)
{
    Move(Battlefield, -Battlefield->GridRef->YLength, ListPosition, "up");
}

void FCharacterBase::WalkDown(FBattlefield* Battlefield, int& ListPosition)
{
    Move(Battlefield, Battlefield->GridRef->YLength, ListPosition, "down");
}

void FCharacterBase::Move(FBattlefield* Battlefield, int Offset, int& ListPosition, const string& Direction)
{
    CurrentBox.bOccupied = false;
    Battlefield->GridRef->GridBoxes[CurrentBox.Index] = CurrentBox;

    CurrentBox = Battlefield->GridRef->GridBoxes[CurrentBox.Index + Offset];
    CurrentBox.bOccupied = true;
    Battlefield->GridRef->GridBoxes[CurrentBox.Index] = CurrentBox;

    Battlefield->PlayerIndexLocations[ListPosition] = CurrentBox.Index;
    cout << "Player " << PlayerIndex << " walked " << Direction << "\n";
}

void FCharacterBase::MoveToEnemy(FBattlefield* Battlefield)
{
    int ListPosition = 0;

    // Find the list position of this character
    for (size_t i = 0; i < Battlefield->PlayerIndexLocations.size(); ++i)
    {
        if (Battlefield->PlayerIndexLocations[i] == CurrentBox.Index)
        {
            ListPosition = static_cast<int>(i);
            break;
        }
    }

    if (CurrentBox.XIndex > Target->CurrentBox.XIndex)
    {
        WalkLeft(Battlefield, ListPosition);
    }
    else if (CurrentBox.XIndex < Target->CurrentBox.XIndex)
    {
        WalkRight(Battlefield, ListPosition);
    }
    else if (CurrentBox.YIndex > Target->CurrentBox.YIndex)
    {
        WalkUp(Battlefield, ListPosition);
    }
    else if (CurrentBox.YIndex < Target->CurrentBox.YIndex)
    {
        WalkDown(Battlefield, ListPosition);
    }
}

void FCharacterBase::Attack()
{
    int CriticalChance = FRandomUtils::GetRandomInt(0, 100);
    float Damage = BaseDamage;

    if (CriticalChance < CriticalHitChance)
    {
        Damage *= DamageMultiplier;
    }

    cout << "Player " << PlayerIndex << " is attacking the player " << Target->PlayerIndex
        << " and did " << Damage << " damage\n";
    Target->TakeDamage(Damage);
}