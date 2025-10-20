#include "FWarrior.h"
#include <iostream>

#include "ECharacterClass.h"
#include "FRandomUtils.h"


using namespace std;

FWarrior* FWarrior::CreateWarrior(const std::string& Name, int PlayerIndex)
{
    const auto Character = new FWarrior();
    Character->Health = 80;
    Character->BaseDamage = 25;
    Character->PlayerIndex = PlayerIndex;
    Character->DamageMultiplier = 1.1f;
    Character->CriticalHitChance = 15;
    Character->CharacterClass = ECharacterClass::Warrior;
    Character->Name = Name + " the warrior";
    Character->Icon = 'W';
    cout << "Player " << PlayerIndex << " Class Choice: " << "Warrior" << "\n";
    return Character;
}

void FWarrior::Attack()
{
    int DoubleDamageChance = FRandomUtils::GetRandomInt(0, 100);
    float Damage = BaseDamage;

    if (DoubleDamageChance <= DoubleDamageProbability)
    {
        Damage *= 2;
        std::cout << "Player " << PlayerIndex << " has done double damage! the player " << Target->PlayerIndex <<
            "  takes " << Damage << " damage\n";
        Target->TakeDamage(Damage);
        return;
    }

    FCharacterBase::Attack();
}