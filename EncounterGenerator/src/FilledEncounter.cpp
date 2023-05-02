#include "FilledEncounter.h"

#include <string>

using namespace Pathfinder;

FilledEncounter::FilledEncounter(const int32_t& adventurerLevel) :
    mAdventurerLevel{adventurerLevel}
{
}

void FilledEncounter::addMonsters(const Monster& monster, uint32_t numMonsters)
{
    mMonsterMap[monster] += numMonsters;
}

void FilledEncounter::removeMonsters(const Monster& monster, uint32_t numMonsters)
{
    if(mMonsterMap.count(monster) != 0)
    {
        if (mMonsterMap[monster] <= numMonsters)
        {
            mMonsterMap.erase(monster);
        }
        else
        {
            mMonsterMap[monster] -= numMonsters;
        }
    }
}

std::map<Monster, uint32_t> FilledEncounter::getMonsterMap() const
{
    return mMonsterMap;
}

uint32_t FilledEncounter::getNumUniqueMonsters() const
{
    return static_cast<uint32_t>(mMonsterMap.size());
}

uint32_t FilledEncounter::getNumTotalMonsters() const
{
    auto numMonsters = 0;
    for (const auto& crNumPair : mMonsterMap)
    {
        numMonsters += crNumPair.second;
    }
    return numMonsters;
}

uint32_t FilledEncounter::getEncounterXp() const
{
    auto battleXp = 0;
    for (const auto &monsterGroup : mMonsterMap)
    {
        battleXp += GeneratorUtilities::getMonsterXp(mAdventurerLevel, monsterGroup.first.getLevel()) * monsterGroup.second;
    }
    return battleXp;
}

std::string FilledEncounter::toString() const
{
    std::string FilledEncounterString = "";
    for (auto monsterPair : mMonsterMap)
    {
        FilledEncounterString += std::to_string(monsterPair.second) + " " + monsterPair.first.getName() + "(" + monsterPair.first.getLocation() + ")" + " : ";
    }
    // Get rid of the fence post stuff.
    FilledEncounterString.pop_back();
    FilledEncounterString.pop_back();
    FilledEncounterString.pop_back();

    return FilledEncounterString;
}

std::string FilledEncounter::toCsvString() const
{
    std::string FilledEncounterString = "";
    for (auto monsterPair : mMonsterMap)
    {
        FilledEncounterString += std::to_string(monsterPair.second) + ","
                            + std::to_string(monsterPair.first.getLevel()) + ","
                            + monsterPair.first.getName() + ","
                            + GeneratorUtilities::toStringCreatureTraits(monsterPair.first.getCreatureTraits()) + ","
                            + monsterPair.first.getLocation() + ",";
    }
    // Get rid of the fence post stuff.
    FilledEncounterString.pop_back();

    return FilledEncounterString;
}

