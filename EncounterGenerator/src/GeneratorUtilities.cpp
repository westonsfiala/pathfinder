#include "GeneratorUtilities.h"

#include <iterator>
#include <map>
#include <sstream>

namespace Pathfinder
{

    uint32_t GeneratorUtilities::getMonsterXp(const int32_t& adventurerLevel, const int32_t& monsterLevel)
    {
        if(monsterLevel < -1)
        {
            return 0;
        }

        auto levelDifference = monsterLevel - adventurerLevel;

        switch (levelDifference)
        {
            case -7: return MONSTER_XP_TABLE[0];
            case -6: return MONSTER_XP_TABLE[1];
            case -5: return MONSTER_XP_TABLE[2];
            case -4: return MONSTER_XP_TABLE[3];
            case -3: return MONSTER_XP_TABLE[4];
            case -2: return MONSTER_XP_TABLE[5];
            case -1: return MONSTER_XP_TABLE[6];
            case 0: return MONSTER_XP_TABLE[7];
            case 1: return MONSTER_XP_TABLE[8];
            case 2: return MONSTER_XP_TABLE[9];
            case 3: return MONSTER_XP_TABLE[10];
            case 4: return MONSTER_XP_TABLE[11];
            case 5: return MONSTER_XP_TABLE[12];
            case 6: return MONSTER_XP_TABLE[13];
            case 7: return MONSTER_XP_TABLE[14];
            default: return 0;
        }

    }

    int32_t GeneratorUtilities::getMonsterLevel(const int32_t& adventurerLevel, const uint32_t& xp)
    {
        const auto xpToLevelMap = generateXpToLevelMap(adventurerLevel);
        if (xpToLevelMap.count(xp))
        {
            return xpToLevelMap.at(xp);
        }

        // No exact match was found. Find the closest while flooring.
        for(auto iter = MONSTER_XP_TABLE.rbegin(); iter != MONSTER_XP_TABLE.rend(); ++iter)
        {
            const auto monsterXp = *iter;
            if(monsterXp < xp)
            {
                return getMonsterLevel(adventurerLevel, monsterXp);
            }
        }

        return -1;
    }

    std::string GeneratorUtilities::toStringDifficulty(const Difficulty& difficulty)
    {
        switch (difficulty)
        {
        case Difficulty::Trivial: return "Trivial";
        case Difficulty::Low: return "Low";
        case Difficulty::Moderate: return "Moderate";
        case Difficulty::Severe: return "Severe";
        case Difficulty::Extreme: return "Extreme";
        default: return "invalid difficulty";
        }
    }

    Difficulty GeneratorUtilities::fromStringDifficulty(const std::string& difficultyString)
    {
        if(difficultyString == "Trivial")
        {
            return Difficulty::Trivial;
        }
        if (difficultyString == "Low")
        {
            return Difficulty::Low;
        }
        if (difficultyString == "Moderate")
        {
            return Difficulty::Moderate;
        }
        if (difficultyString == "Severe")
        {
            return Difficulty::Severe;
        }
        if (difficultyString == "Extreme")
        {
            return Difficulty::Extreme;
        }
        return Difficulty::INVALID;
    }

    std::string GeneratorUtilities::toStringCreatureSize(const CreatureSize& creatureSize)
    {
        switch (creatureSize)
        {
        case CreatureSize::Tiny: return "Tiny";
        case CreatureSize::Small: return "Small";
        case CreatureSize::Medium: return "Medium";
        case CreatureSize::Large: return "Large";
        case CreatureSize::Huge: return "Huge";
        case CreatureSize::Gargantuan: return "Gargantuan";
        default: return "Invalid Creature Size";
        }
    }

    CreatureSize GeneratorUtilities::fromStringCreatureSize(const std::string& creatureSizeString)
    {
        if (creatureSizeString == "Tiny")
        {
            return CreatureSize::Tiny;
        }
        if (creatureSizeString == "Small")
        {
            return CreatureSize::Tiny;
        }
        if (creatureSizeString == "Medium")
        {
            return CreatureSize::Tiny;
        }
        if (creatureSizeString == "Large")
        {
            return CreatureSize::Tiny;
        }
        if (creatureSizeString == "Huge")
        {
            return CreatureSize::Tiny;
        }
        if (creatureSizeString == "Gargantuan")
        {
            return CreatureSize::Tiny;
        }
        return CreatureSize::INVALID;
    }

    std::string GeneratorUtilities::toStringCreatureTraits(const std::vector<std::string>& creatureTraits)
    {
        std::stringstream  s;
        std::copy(creatureTraits.begin(), creatureTraits.end(), std::ostream_iterator<std::string>(s, ";"));
        return s.str();
    }

    std::vector<std::string> GeneratorUtilities::fromStringCreatureTraits(const std::string& creatureTraitsString)
    {
        std::vector<std::string> tokens;
        std::string trait;
        std::istringstream traitStream(creatureTraitsString);

        while (std::getline(traitStream, trait, ';')) {
            tokens.push_back(trait);
        }

        return tokens;
    }

    std::map<uint32_t, int32_t> GeneratorUtilities::generateXpToLevelMap(const int32_t& adventurerLevel)
    {
        std::map<uint32_t, int32_t> xpToLevelMap;

        for(auto levelMod = -7; levelMod < 7; ++levelMod)
        {
            auto monsterLevel = adventurerLevel + levelMod;
            auto monsterXp = getMonsterXp(adventurerLevel, monsterLevel);
            if(monsterXp != 0)
            {
                xpToLevelMap[monsterXp] = monsterLevel;
            }
        }
        return xpToLevelMap;
    }
}
