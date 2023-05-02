#pragma once
#include "Encounter.h"
#include "FilledEncounter.h"
#include "Monster.h"

using namespace Pathfinder;

/**
 * \brief A MonsterList is a wrapper around a vector of monsters with some helper methods for turning encounters into filled encounters.
 */
class MonsterList
{
public:
    MonsterList();
    ~MonsterList() = default;

    /**
     * \brief Add a monster to the list.
     * \param monster Monster to add to the list.
     */
    void addMonster(const Monster& monster);

    /**
     * \brief Remove a monster from the list.
     * \param monster Monster to remove from the list.
     */
    void removeMonster(const Monster& monster);

    /**
     * \brief Take a encounter and fill it up with monsters.
     * \param encounter Encounter to fill up.
     * \return A filled encounter with monster.
     */
    FilledEncounter fillEncounter(const Encounter& encounter) const;

    /**
     * \brief Take many encounters and fill them up with monsters.
     * \param encounters Encounters to fill up.
     * \return A vector of filled encounters.
     */
    std::vector<FilledEncounter> fillEncounters(const std::vector<Encounter>& encounters) const;

private:

    /**
     * \brief Filters the list of monsters by the given level.
     * \param level Level to filter the monsters by.
     * \return MonsterList consisting of only monsters of the given level.
     */
    MonsterList filteredListByLevel(const int32_t& level) const;
    /**
     * \brief Filters the list of monsters by the given creature type.
     * \param creatureTrait Single trait of the monster to filter by.
     * \return MonsterList consisting of only monsters of the given creature traits.
     */
    MonsterList filteredListByCreatureTrait(const std::string& creatureTrait) const;

    /**
     * \brief Gets a random monster from the list of available monsters.
     * \return Random monster.
     */
    Monster getRandomMonster();

    std::vector<Monster> mMonsters;
};
