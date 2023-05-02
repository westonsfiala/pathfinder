#include "MonsterList.h"

#include <algorithm>
#include <chrono>
#include <random>

using namespace Pathfinder;

MonsterList::MonsterList()
{
}

void MonsterList::addMonster(const Monster& monster)
{
    mMonsters.push_back(monster);
}

void MonsterList::removeMonster(const Monster& monster)
{
    std::remove_if(mMonsters.begin(), mMonsters.end(), [monster](const Monster& checkMonster) { return monster == checkMonster; });
}

FilledEncounter MonsterList::fillEncounter(const Encounter& encounter) const
{
    FilledEncounter newEncounter(encounter.getEncounterLevel());

    std::vector<std::string> foundTraits;
    bool hasFoundType = false;

    for(const auto& monsterPair : encounter.getMonsterLevelToCountMap())
    {
        auto filteredList = filteredListByLevel(monsterPair.first);

        // If we have already found a type, try to match found monsters to that list.
        // If we don't have any monsters that can match though, it gives up.
        if(hasFoundType)
        {
            std::vector<MonsterList> possibleLists;
            for(auto possibleTrait : foundTraits)
            {
                // These traits make no sense to filter off of.
                if(possibleTrait == "Uncommon" || possibleTrait == "Rare" || possibleTrait == "Unique")
                {
                    continue;
                }

                auto typeMatchedFilteredList = filteredList.filteredListByCreatureTrait(possibleTrait);
                if (!typeMatchedFilteredList.mMonsters.empty())
                {
                    possibleLists.push_back(typeMatchedFilteredList);
                    break;
                }
            }

            // Choose the smallest list as that is more likely to give us options that are more of the same.
            // May not be perfect, but eh whatever.
            for(auto possibleList : possibleLists)
            {
                if(possibleList.mMonsters.size() < filteredList.mMonsters.size())
                {
                    filteredList = possibleList;
                }
            }
        }

        // We aren't guaranteed to always have monsters of what level we are looking for. Looking at you non-existent level 25+ monsters.
        // If that happens, just start going downwards until we find something. Or eventually give if we are already at -1.
        auto wantedLevel = monsterPair.first;
        while(filteredList.mMonsters.empty() && wantedLevel != -1)
        {
            wantedLevel = wantedLevel - 1;
            filteredList = filteredListByLevel(wantedLevel);
        }

        auto randomMonster = filteredList.getRandomMonster();
        newEncounter.addMonsters(randomMonster, monsterPair.second);

        hasFoundType = true;
        foundTraits = randomMonster.getCreatureTraits();
    }

    return newEncounter;
}

std::vector<FilledEncounter> MonsterList::fillEncounters(const std::vector<Encounter>& encounters) const
{
    std::vector<FilledEncounter> filledEncounters;

    for(const auto& encounter : encounters)
    {
        auto filledEncounter = fillEncounter(encounter);
        filledEncounters.push_back(filledEncounter);
    }

    return filledEncounters;
}

MonsterList MonsterList::filteredListByLevel(const int32_t& level) const
{
    MonsterList filteredList;

    for(const auto& monster : mMonsters)
    {
        if(monster.getLevel() == level)
        {
            filteredList.addMonster(monster);
        }
    }

    return filteredList;
}

MonsterList MonsterList::filteredListByCreatureTrait(const std::string& creatureTrait) const
{
    MonsterList filteredList;

    for (const auto& monster : mMonsters)
    {
        if (monster.hasCreatureTrait(creatureTrait))
        {
            filteredList.addMonster(monster);
        }
    }

    return filteredList;
}

Monster MonsterList::getRandomMonster()
{
    const auto seed = static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine engine(seed);
    const std::uniform_int_distribution<int> dist(0, static_cast<int>(mMonsters.size()-1));

    return mMonsters[dist(engine)];
}
