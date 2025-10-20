#pragma once
#include <string>
#include "FCharacterBase.h"

class FCleric : public FCharacterBase
{
public:
    static FCleric* CreateCleric(const std::string& Name, int PlayerIndex);

    int HealthRegenProbability = 25;
    float HealAmount = 5;

    void Attack() override;
};