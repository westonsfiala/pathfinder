#include "FileHelper.h"

#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

#include "Monster.h"

using namespace Pathfinder;
using namespace nlohmann;

MonsterList FileHelper::parseJson(const std::string& jsonFilePath, bool parseUnique)
{
    auto monsterList = MonsterList();

    std::ifstream ifs(jsonFilePath);
    json parsedJson = json::parse(ifs);

    for(const auto& monsterObject : parsedJson)
    {
        auto parsedLevel = monsterObject["Level"].get<int32_t>();
        auto parsedRarity = monsterObject["Rarity"].get<std::string>();
        auto parsedName = monsterObject["Name"].get<std::string>();
        auto parsedTraits = monsterObject["Traits"].get<std::string>();
        auto parsedSize = monsterObject["Size"].get<std::string>();
        auto parsedLocation = monsterObject["Source"].get<std::string>();

        Monster newMonster(
            parsedName, 
            parsedLevel,
            GeneratorUtilities::fromStringCreatureSize(parsedSize), 
            GeneratorUtilities::fromStringCreatureTraits(parsedTraits),
            parsedLocation
        );

        auto isUnique = parsedRarity == "Unique";

        if (!isUnique || (parseUnique && isUnique))
        {
            monsterList.addMonster(newMonster);

            if (!isUnique)
            {
                if (parsedLevel != -1)
                {
                    Monster weakNewMonster(
                        "Weak " + parsedName,
                        parsedLevel - 1,
                        GeneratorUtilities::fromStringCreatureSize(parsedSize),
                        GeneratorUtilities::fromStringCreatureTraits(parsedTraits),
                        parsedLocation
                    );

                    monsterList.addMonster(weakNewMonster);
                }

                Monster eliteNewMonster(
                    "Elite " + parsedName,
                    parsedLevel + 1,
                    GeneratorUtilities::fromStringCreatureSize(parsedSize),
                    GeneratorUtilities::fromStringCreatureTraits(parsedTraits),
                    parsedLocation
                );

                monsterList.addMonster(eliteNewMonster);
            }
        }
    }

    return monsterList;
}

void FileHelper::writeToFile(const std::string& filePath, const std::string& fileContent)
{
    std::ofstream out(filePath);
    out << fileContent;
    out.close();
}
