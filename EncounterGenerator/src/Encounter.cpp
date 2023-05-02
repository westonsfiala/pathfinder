#include "Encounter.h"

#include <string>

using namespace Pathfinder;

Encounter::Encounter(const int32_t& adventurerLevel) :
    mAdventurerLevel{adventurerLevel}
{
}

int32_t Encounter::getEncounterLevel() const
{
    return mAdventurerLevel;
}

void Encounter::addMonsters(int32_t level, uint32_t numMonsters)
{
    mMonsterLevelToCountMap[level] += numMonsters;
}

void Encounter::removeMonsters(int32_t level, uint32_t numMonsters)
{
    if(mMonsterLevelToCountMap.count(level) != 0)
    {
        if (mMonsterLevelToCountMap[level] <= numMonsters)
        {
            mMonsterLevelToCountMap.erase(level);
        }
        else
        {
            mMonsterLevelToCountMap[level] -= numMonsters;
        }
    }
}

std::map<int32_t, uint32_t> Encounter::getMonsterLevelToCountMap() const
{
    return mMonsterLevelToCountMap;
}

uint32_t Encounter::getNumUniqueMonsters() const
{
    return static_cast<uint32_t>(mMonsterLevelToCountMap.size());
}

uint32_t Encounter::getNumTotalMonsters() const
{
    auto numMonsters = 0;
    for (const auto& levelNumPair : mMonsterLevelToCountMap)
    {
        numMonsters += levelNumPair.second;
    }
    return numMonsters;
}

uint32_t Encounter::getEncounterXp() const
{
    auto battleXp = 0;
    for (const auto &monsterGroup : mMonsterLevelToCountMap)
    {
        battleXp += GeneratorUtilities::getMonsterXp(mAdventurerLevel, monsterGroup.first) * monsterGroup.second;
    }
    return battleXp;
}

std::string Encounter::toString() const
{
    std::string encounterString = "";
    for (auto monsterPair : mMonsterLevelToCountMap)
    {
        encounterString += std::to_string(monsterPair.second) + " level " + std::to_string(monsterPair.first) + " : ";
    }
    // Get rid of the fence post stuff.
    encounterString.pop_back();
    encounterString.pop_back();
    encounterString.pop_back();

    return encounterString;
}

