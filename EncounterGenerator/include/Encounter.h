#pragma once
#include "GeneratorUtilities.h"

#include <map>

using namespace Pathfinder;

/**
 * \brief An Encounter is a mapping of level and the number of monsters of that level.
 */
class Encounter
{
public:
    Encounter(const int32_t& adventurerLevel);
    ~Encounter() = default;

    /**
     * \brief Returns the level of adventurers involved in this encounter.
     * \return Level of adventurers involved in this encounter.
     */
    int32_t getEncounterLevel() const;

    /**
     * \brief Add monsters to this encounter.
     * \param level The level of the monsters you want to add.
     * \param numMonsters The number of monsters you want to add.
     */
    void addMonsters(int32_t level, uint32_t numMonsters);

    /**
     * \brief Remove monsters from this encounter.
     * \param level The level of the monsters you want to remove.
     * \param numMonsters The number of monsters you want to remove.
     */
    void removeMonsters(int32_t level, uint32_t numMonsters);

    /**
     * \brief Get the monster levels that are in this encounter and how many of them there are.
     * \return Monster level map of this encounter.
     */
    std::map<int32_t, uint32_t> getMonsterLevelToCountMap() const;

    /**
     * \brief Get the number of unique monsters in this encounter.
     * \return Number of unique monsters in this encounter.
     */
    uint32_t getNumUniqueMonsters() const;

    /**
     * \brief Get the total number of monsters in this encounter.
     * \return Number of total monsters in this counter.
     */
    uint32_t getNumTotalMonsters() const;

    /**
     * \brief Gets the xp rewards for this encounter.
     * \return Xp reward for this encounter.
     */
    uint32_t getEncounterXp() const;

    /**
     * \brief Converts the current encounter into a string.
     *
     * Has the form "X level Y : A level B ...".
     * \return String form of the encounter.
     */
    std::string toString() const;

private:
    int32_t mAdventurerLevel;
    std::map<int32_t, uint32_t> mMonsterLevelToCountMap;

};
