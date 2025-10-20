#include "FArcher.h"
#include <iostream>

#include "ECharacterClass.h"
#include "FRandomUtils.h"

using namespace std;

FArcher* FArcher::CreateArcher(const std::string& Name, int PlayerIndex)
{
    auto Character = new FArcher();
    Character->Health = 100;
    Character->BaseDamage = 20;
    Character->PlayerIndex = PlayerIndex;
    Character->DamageMultiplier = 1.5f;
    Character->CriticalHitChance = 25;
    Character->CharacterClass = ECharacterClass::Archer;
    Character->Name = Name + " the archer";
    Character->Icon = 'A';
    cout << "Player " << PlayerIndex << " Class Choice: " << "Archer" << "\n";
    return Character;
}

void FArcher::Attack()
{
    int MultipleAttackChance = FRandomUtils::GetRandomInt(0, 100);

    if (MultipleAttackChance <= MultipleAttackProbability)
    {
        std::cout << "Player " << PlayerIndex << " has used multiple attacks!\n";
        int Hits = FRandomUtils::GetRandomInt(MinAttacks, MaxAttacks);
        for (int i = 0; i < Hits; i++) {
            FCharacterBase::Attack();
        }
        return;
    }

    FCharacterBase::Attack();
}