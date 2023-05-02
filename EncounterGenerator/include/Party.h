#pragma once
#include "GeneratorUtilities.h"

#include <map>

using namespace Pathfinder;

/**
 * \brief A party is made up of a number of adventurers and has desired XP for each difficulty.
 */
class Party
{
public:

    /**
     * \brief Creates a party of a number of adventurers of a given level.
     * \param level Level of the adventurer. Must be between 1 -> 20 inclusive.
     * \param count Number of adventurers.
     */
    Party(const int32_t& level, const uint32_t& count);
    Party(const Party& other) = default;
    ~Party() = default;

    /**
     * \brief Gets the level of adventurers in the party.
     * \return Level of adventurers.
     */
    uint32_t getLevel() const;

    /**
     * \brief Gets the number of adventurers in the party.
     * \return Number of adventurers.
     */
    uint32_t getNumAdventurers() const;

    /**
     * \brief Gets the desired XP for a battle of the given difficulty.
     * \param difficulty Difficulty of the battle.
     * \return XP that is desired by the party at the given difficulty.
     */
    uint32_t getDesiredXp(const Difficulty& difficulty) const;

    /**
     * \brief Gets the lower bound of the desired XP for a battle of the given difficulty.
     * \param difficulty Difficulty of the battle.
     * \return Lower XP bound that is desired by the party at the given difficulty.
     */
    uint32_t getLowerDesiredXp(const Difficulty& difficulty) const;

    /**
     * \brief Gets the upper bound of the desired XP for a battle of the given difficulty.
     * \param difficulty Difficulty of the battle.
     * \return Upper XP bound that is desired by the party at the given difficulty.
     */
    uint32_t getUpperDesiredXp(const Difficulty& difficulty) const;

private:

    static const float UPPER_XP_MODIFIER;
    static const float LOWER_XP_MODIFIER;

    /**
     * \brief Calculates the desired xp of the party & stores it for quick access later.
     */
    void calculateDesiredXp();

    /**
     * \brief Gets the desired battle XP for the given difficulty.
     * \param difficulty Difficulty of the battle.
     * \return XP that is desired for this battle.
     */
    uint32_t getBattleXp(const Difficulty& difficulty) const;

    int32_t mAdventurerLevel;
    uint32_t mAdventurerCount;
    std::map<Difficulty, uint32_t> mDesiredXpMap;

};

