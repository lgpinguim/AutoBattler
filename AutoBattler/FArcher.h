#pragma once
#include <string>
#include "FCharacterBase.h"

class FArcher : public FCharacterBase
{
public:
    static FArcher* CreateArcher(const std::string& Name, int PlayerIndex);

    int MultipleAttackProbability = 20;
    int MaxAttacks = 4;
    int MinAttacks = 2;

    void Attack() override;
};