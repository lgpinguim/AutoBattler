#include "FGameManager.h"
#include "FRandomUtils.h"
#include <iostream>

#include "FCharacterFactory.h"
#include "FRandomUtils.h"

using namespace std;

FGameManager::FGameManager() = default;

void FGameManager::SetupBattlefield()
{
    int Lines = 0;
    int Columns = 0;

    Battlefield = new FBattlefield();
    Battlefield->ValidateBattlefieldDimensions(Lines, Columns);
    Battlefield->GridRef = Battlefield->CreateBattlefield(Lines, Columns);
}

void FGameManager::SetupPlayers()
{
    FCharacterBase* PlayerCharacter = new FCharacterBase();
    int ClassIndex = PlayerCharacter->ValidateCreationInput();
    string Name = PlayerCharacter->CreateCharacterName();
    PlayerCharacter = FCharacterFactory::CreateCharacter(ClassIndex, Name, 1);
    AllPlayers.push_back(PlayerCharacter);

    // Enemy creation
    ClassIndex = FRandomUtils::GetRandomInt(1, 4);
    Name = "Anakin";
    FCharacterBase* EnemyCharacter = FCharacterFactory::CreateCharacter(ClassIndex, Name, 2);
    AllPlayers.push_back(EnemyCharacter);

    PlayerCharacter->SetTarget(EnemyCharacter);
    EnemyCharacter->SetTarget(PlayerCharacter);
}

void FGameManager::AllocatePlayersOnBattlefield() const
{
    for (FCharacterBase* Player : AllPlayers)
    {
        Battlefield->AllocatePlayer(Player);
    }
}

void FGameManager::SetupGame()
{
    bGameEnd = false;
    CurrentTurn = 0;

    SetupPlayers();
    SetupBattlefield();
    AllocatePlayersOnBattlefield();

    Battlefield->DrawBattlefield(AllPlayers);
}

void FGameManager::FlipPlayerTurn(int& StartingPlayer)
{
    StartingPlayer = (StartingPlayer == 0) ? 1 : 0;
}

void FGameManager::StartGame()
{
    SetupGame();

    int StartingPlayer = FRandomUtils::GetRandomInt(0, 1);

    while (!bGameEnd)
    {
        StartTurn();

        if (!bGameEnd)
        {
            cout << "Current turn: " << ++CurrentTurn << "\n";
            HandleTurn(AllPlayers[StartingPlayer]);
        }

        FlipPlayerTurn(StartingPlayer);
    }
}

void FGameManager::StartTurn()
{
    if (AllPlayers[0]->Health <= 0)
    {
        cout << "\nGAME OVER! You lost the game!\n";
        EndGame();
    }
    else if (AllPlayers[1]->Health <= 0)
    {
        cout << "\nCongratulations! " << AllPlayers[0]->Name << " won the game!\n";
        EndGame();
    }
    else if (!bGameEnd)
    {
        printf("\n");
        system("pause");
        printf("\n");
    }
}

void FGameManager::HandleTurn(FCharacterBase* Player) const
{
    bool bCanAttack = Player->CheckCloseTargets(Battlefield->GridRef);
    if (bCanAttack)
    {
        Player->Attack();
    }
    else
    {
        Player->MoveToEnemy(Battlefield);
        Battlefield->DrawBattlefield(AllPlayers);

        bCanAttack = Player->CheckCloseTargets(Battlefield->GridRef);
        if (bCanAttack)
        {
            Player->Attack();
        }
    }
}

void FGameManager::EndGame()
{
    cout << "The game has ended!";
    bGameEnd = true;
    cout << "\nPlay again? (y/n): ";
    string Input;
    getline(cin, Input);

    if (Input == "y" || Input == "Y")
    {
        for (FCharacterBase* Player : AllPlayers)
        {
            delete Player;
        }

        AllPlayers.clear();
        delete Battlefield;

        system("cls");
        StartGame();
    }
    else
    {
        bGameEnd = true;
        cout << "Thank you for playing!";
    }
}
