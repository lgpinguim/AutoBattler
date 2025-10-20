#include "FCleric.h"
#include <iostream>

#include "ECharacterClass.h"
#include "FRandomUtils.h"

using namespace std;

FCleric* FCleric::CreateCleric(const std::string& Name, int PlayerIndex)
{
    const auto Character = new FCleric();
    Character->Health = 100;
    Character->BaseDamage = 15;
    Character->PlayerIndex = PlayerIndex;
    Character->DamageMultiplier = 3.0f;
    Character->CriticalHitChance = 15;
    Character->CharacterClass = ECharacterClass::Cleric;
    Character->Name = Name + " the cleric";
    Character->Icon = 'C';
    cout << "Player " << PlayerIndex << " Class Choice: " << "Cleric" << "\n";
    return Character;
}

void FCleric::Attack()
{
    int HealthRegenChance = FRandomUtils::GetRandomInt(0, 100);

    if (HealthRegenChance <= HealthRegenProbability)
    {
        Health += HealAmount;
        std::cout << "Player " << PlayerIndex << " has healed for " << HealAmount << " hp!\n";
    }

    FCharacterBase::Attack();
}