#pragma once
#include <string>

#include "GeneratorUtilities.h"

using namespace Pathfinder;

/**
 * \brief A Monster is a creature used in encounters. It stores useful information about the creature and where to find more info.
 */
class Monster
{
public:
    Monster(const std::string& name, const int32_t& level, const CreatureSize& creatureSize, const std::vector<std::string>& creatureTraits, const std::string& location);
    Monster(const Monster& other) = default;
    ~Monster() = default;

    bool operator==(const Monster& other) const;
    bool operator<(const Monster& other) const;

    /**
     * \brief Checks to see if the monster has all of the information needed to be used.
     * \return If any of the field for this monster are not filled out will return false.
     */
    bool isValid() const;

    /**
     * \brief Gets the name of the monster.
     * \return Name of the monster.
     */
    std::string getName() const;

    /**
     * \brief Gets the level of the monster.
     * \return Level of the monster.
     */
    int32_t getLevel() const;

    /**
     * \brief Gets the creature size of the monster.
     * \return Creature size of the monster.
     */
    CreatureSize getCreatureSize() const;

    /**
     * \brief Gets the creature traits of the monster.
     * \return Creature traits of the monster
     */
    std::vector<std::string> getCreatureTraits() const;

    /**
     * \brief If the monster has the given trait.
     * \return If the monster has the given trait.
     */
    bool hasCreatureTrait(const std::string& trait) const;

    /**
     * \brief Gets the location of the monster.
     * \return Location of the monster.
     */
    std::string getLocation() const;

private:
    std::string mName;
    int32_t mLevel;
    CreatureSize mCreatureSize;
    std::vector<std::string> mCreatureTraits;
    std::string mLocation;
};
