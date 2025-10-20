#pragma once

#include <string>
#include "FCharacterBase.h"

class FCharacterFactory
{
public:
    static FCharacterBase* CreateCharacter(int ClassIndex, const std::string& Name, int PlayerIndex);
};
