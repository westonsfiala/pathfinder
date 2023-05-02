#include "Party.h"
#include "EncounterGenerator.h"
#include "GeneratorUtilities.h"

using namespace Pathfinder;

constexpr float Party::UPPER_XP_MODIFIER = 1.10f;
constexpr float Party::LOWER_XP_MODIFIER = 0.9f;

Party::Party(const int32_t& level, const uint32_t& count)
{
    // Only add an adventurer when the level is valid.
    if (level >= 1 && level <= 20)
    {
        mAdventurerLevel = level;
        mAdventurerCount = count;
        calculateDesiredXp();
    }
}

uint32_t Party::getLevel() const
{
    return mAdventurerLevel;
}

uint32_t Party::getNumAdventurers() const
{
    return mAdventurerCount;
}

uint32_t Party::getDesiredXp(const Difficulty& difficulty) const
{
    if(mDesiredXpMap.count(difficulty) != 0)
    {
        return mDesiredXpMap.at(difficulty);
    }

    return 0;
}

uint32_t Party::getLowerDesiredXp(const Difficulty& difficulty) const
{
    if (mDesiredXpMap.count(difficulty) != 0)
    {
        return static_cast<uint32_t>(mDesiredXpMap.at(difficulty) * LOWER_XP_MODIFIER);
    }

    return 0;
}

uint32_t Party::getUpperDesiredXp(const Difficulty& difficulty) const
{
    if (mDesiredXpMap.count(difficulty) != 0)
    {
        return static_cast<uint32_t>(mDesiredXpMap.at(difficulty) * UPPER_XP_MODIFIER);
    }

    return 0;
}

void Party::calculateDesiredXp()
{
    for(const auto& diff : DIFFICULTY_VECTOR)
    {
        mDesiredXpMap[diff] = getBattleXp(diff);
    }
}

uint32_t Party::getBattleXp(const Difficulty& difficulty) const
{
    if (difficulty < Difficulty::Trivial || difficulty > Difficulty::Extreme)
    {
        return 0;
    }

    auto desiredXp = 0;

    // Get their desired xp and multiply it by the number of adventurers. 
    desiredXp += ADVENTURER_XP_BUDGET.at(difficulty) * mAdventurerCount;

    return desiredXp;
}
