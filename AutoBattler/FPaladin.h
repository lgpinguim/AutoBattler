#pragma once
#include "FCharacterBase.h"

class FPaladin : public FCharacterBase
{
public:
    static FPaladin* CreatePaladin(const std::string& Name, int PlayerIndex);

    int BlockDamageProbability = 25;

    void TakeDamage(float& Amount) override;
};