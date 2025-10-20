#include "FCharacterFactory.h"

#include "FArcher.h"
#include "FCleric.h"
#include "FCharacterBase.h"
#include "FPaladin.h"
#include "FWarrior.h"

FCharacterBase* FCharacterFactory::CreateCharacter(int ClassIndex, const std::string& Name, int PlayerIndex)
{
    FCharacterBase* Character = new FCharacterBase();

    switch (ClassIndex)
    {
    case 1:
        Character = FPaladin::CreatePaladin(Name, PlayerIndex);
        break;
    case 2:
        Character = FWarrior::CreateWarrior(Name, PlayerIndex);
        break;
    case 3:
        Character = FCleric::CreateCleric(Name, PlayerIndex);
        break;
    case 4:
        Character = FArcher::CreateArcher(Name, PlayerIndex);
        break;
    default:
        break;
    }

    return Character;
}
