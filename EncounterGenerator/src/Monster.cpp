#include "Monster.h"

Monster::Monster(const std::string& name, const int32_t& level, const CreatureSize& creatureSize, const std::vector<std::string>& creatureTraits, const std::string& location) :
    mName{ name },
    mLevel{ level },
    mCreatureSize{ creatureSize },
    mCreatureTraits{ creatureTraits },
    mLocation{ location }
{
}

bool Monster::operator==(const Monster& other) const
{

    if(mName != other.mName)
    {
        return false;
    }
    if (mLevel != other.mLevel)
    {
        return false;
    }
    if (mCreatureSize != other.mCreatureSize)
    {
        return false;
    }
    if (mCreatureTraits != other.mCreatureTraits)
    {
        return false;
    }
    if (mLocation != other.mLocation)
    {
        return false;
    }
    return true;
}

bool Monster::operator<(const Monster& other) const
{
    if(mLevel != other.mLevel)
    {
        return mLevel < other.mLevel;
    }

    return mName < other.mName;
}

bool Monster::isValid() const
{
    if (mName.empty())
    {
        return false;
    }
    if(mLevel >= -1 && mLevel <= 30)
    {
        return false;
    }
    if(mCreatureSize == CreatureSize::INVALID)
    {
        return false;
    }
    if(mCreatureTraits.empty())
    {
        return false;
    }
    if(mLocation.empty())
    {
        return false;
    }
    return true;
}

std::string Monster::getName() const
{
    return mName;
}

int32_t Monster::getLevel() const
{
    return mLevel;
}

CreatureSize Monster::getCreatureSize() const
{
    return mCreatureSize;
}

std::vector<std::string> Monster::getCreatureTraits() const
{
    return mCreatureTraits;
}

bool Monster::hasCreatureTrait(const std::string& trait) const
{
    return std::find(mCreatureTraits.begin(), mCreatureTraits.end(), trait) != mCreatureTraits.end();
}

std::string Monster::getLocation() const
{
    return mLocation;
}
