#pragma once
#include <string>
#include "FCharacterBase.h"

class FWarrior : public FCharacterBase
{
public:
    static FWarrior* CreateWarrior(const std::string& Name, int PlayerIndex);

    int DoubleDamageProbability = 25;

    void Attack() override;
};