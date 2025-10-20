#include "FPaladin.h"
#include <iostream>

#include "ECharacterClass.h"
#include "FRandomUtils.h"

using namespace std;

FPaladin* FPaladin::CreatePaladin(const std::string& Name, int PlayerIndex) 
{
    const auto Character = new FPaladin();
    Character->Health = 130;
    Character->BaseDamage = 20;
    Character->PlayerIndex = PlayerIndex;
    Character->DamageMultiplier = 1.1f;
    Character->CriticalHitChance = 10;
    Character->CharacterClass = ECharacterClass::Paladin;
    Character->Name = Name + " the paladin ";
    Character->Icon = 'P';
    cout << "Player " << PlayerIndex << " Class Choice: " << "Paladin" << "\n";
    return Character;
}

void FPaladin::TakeDamage(float& Amount)
{
    int BlockDamageChance = FRandomUtils::GetRandomInt(0, 100);

    if (BlockDamageChance <= BlockDamageProbability)
    {
        std::cout << "Player " << PlayerIndex << " has blocked the damage! player " << Target->PlayerIndex <<
            "  did  0" << " damage\n";
    }
    else
    {
        if ((Health -= Amount) <= 0)
        {
            Die();
        }
    }
}