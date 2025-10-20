#pragma once

#include <vector>
#include <string>
#include "FBattlefield.h"
#include "FCharacterBase.h"

class FGameManager
{
public:
    FGameManager();

    // Core Methods
    void SetupGame();
    void StartGame();
    void EndGame();

private:
    // Helper Methods
    void SetupBattlefield();
    void SetupPlayers();
    void AllocatePlayersOnBattlefield() const;
    void StartTurn();
    void HandleTurn(FCharacterBase* Player) const;
    static void FlipPlayerTurn(int& StartingPlayer);

private:
    FBattlefield* Battlefield = nullptr;
    std::vector<FCharacterBase*> AllPlayers;

    bool bGameEnd = false;
    int CurrentTurn = 0;
};
