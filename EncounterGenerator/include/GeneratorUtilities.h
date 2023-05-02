#pragma once
#include <map>
#include <vector>

namespace Pathfinder
{

/**
 * \brief Set difficulties for a battle.
 */
enum class Difficulty
{
    Trivial,
    Low,
    Moderate,
    Severe,
    Extreme,
    INVALID
};

/**
 * \brief Vector of all the difficulties.
 */
static const std::vector<uint32_t> MONSTER_XP_TABLE = {
    9,
    12,
    14,
    18,
    21,
    26,
    32,
    40,
    48,
    60,
    72,
    90,
    108,
    135,
    160
};

/**
 * \brief Vector of all the difficulties.
 */
static const std::vector<Difficulty> DIFFICULTY_VECTOR = {
    Difficulty::Trivial,
    Difficulty::Low,
    Difficulty::Moderate,
    Difficulty::Severe,
    Difficulty::Extreme
};

/**
 * \brief XP budget for each adventurer at difficult 
 */
static const std::map<Difficulty, uint32_t> ADVENTURER_XP_BUDGET = {
    {Difficulty::Trivial, 10},
    {Difficulty::Low, 15},
    {Difficulty::Moderate, 20},
    {Difficulty::Severe, 30},
    {Difficulty::Extreme, 40}
};

/**
 * \brief Allowed Sizes for all monsters.
 */
enum class CreatureSize
{
    Tiny = 0,
    Small,
    Medium,
    Large,
    Huge,
    Gargantuan,
    INVALID
};

class GeneratorUtilities
{
public:

    /**
     * \brief Gets the xp that a monster of the given CR will reward.
     * \param adventurerLevel Level of the adventurer
     * \param monsterLevel Level of the monster
     * \return XP to award for defeating the monster for a given adventure level
     */
    static uint32_t getMonsterXp(const int32_t &adventurerLevel, const int32_t &monsterLevel);

    /**
     * \brief Gets the level of a monster from how much xp it awards.
     * \param adventurerLevel Level of the adventurer.
     * \param xp XP of the monster.
     * \return Level of the monster with the given XP reward. If no exact match is found, finds the nearest, by flooring.
     */
    static int32_t getMonsterLevel(const int32_t& adventurerLevel, const uint32_t &xp);

    /**
     * \brief Turns the given difficulty into its string representation.
     * \param difficulty Difficult to turn into a string.
     * \return String representation of the difficulty.
     */
    static std::string toStringDifficulty(const Difficulty &difficulty);

    /**
     * \brief Finds the difficulty from the given string.
     * \param difficultyString String representation of a difficulty.
     * \return Difficulty found from the given string. If no match is found, returns INVALID.
     */
    static Difficulty fromStringDifficulty(const std::string &difficultyString);

    /**
     * \brief Turns the given Size into its string representation.
     * \param creatureSize Size to turn into a string.
     * \return String representation of the size.
     */
    static std::string toStringCreatureSize(const CreatureSize &creatureSize);

    /**
     * \brief Finds the creature size from the given string.
     * \param creatureSizeString String representation of a creature size.
     * \return Creature size found from the given string. If no match is found, returns INVALID.
     */
    static CreatureSize fromStringCreatureSize(const std::string &creatureSizeString);

    /**
     * \brief Turns the given vector of traits into a semicolon divided string representation.
     * \param creatureTraits Vector of traits.
     * \return String representation of the traits with semicolon dividers.
     */
    static std::string toStringCreatureTraits(const std::vector<std::string> &creatureTraits);

    /**
     * \brief Splits the given string representation of creature traits by dividing semicolons.
     * \param creatureTraitsString String representation of a creature traits divided by semicolons.
     * \return Vector of traits.
     */
    static std::vector<std::string> fromStringCreatureTraits(const std::string &creatureTraitsString);

private:

    /**
     * \brief Generates a map that pairs the xp a monster would award to its level.
     * \param adventurerLevel Level of the adventurer.
     * \return Map of monster xp to monster level.
     */
    static std::map<uint32_t, int32_t> generateXpToLevelMap(const int32_t& adventurerLevel);
};
}
