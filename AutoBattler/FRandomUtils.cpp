#include "FRandomUtils.h"

int FRandomUtils::GetRandomInt(int Min, int Max)
{
    std::uniform_int_distribution<> Distribution(Min, Max);
    std::random_device RandomDevice;
    std::default_random_engine Generator(RandomDevice());
    return Distribution(Generator);
}
