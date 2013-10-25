/*
 * Copyright 2013 biegleux
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _RECANALYSTWRAP_H_
#define _RECANALYSTWRAP_H_
#include <string>
#include <vector>
#include <map>
#include <exception>
#include <memory>
#include "recanalyst.h"

namespace RecAnalystWrapper {

  enum class StartingAge {
    DARK_AGE,
    FEUDAL_AGE,
    CASTLE_AGE,
    IMPERIAL_AGE,
    POSTIMPERIAL_AGE
  };

  enum class Civilization {
    BRITONS,
    FRANKS,
    GOTHS,
    TEUTONS,
    JAPANESE,
    CHINESE,
    BYZANTINES,
    PERSIANS,
    SARACENS,
    TURKS,
    VIKINGS,
    MONGOLS,
    CELTS,
    SPANISH,
    AZTECS,
    MAYANS,
    HUNS,
    KOREANS,
    ITALIANS,
    INDIANS,
    INCAS,
    MAGYARS,
    SLAVS
  };

  enum class PlayerColor {
    UNDEFINED,
    BLUE,
    RED,
    GREEN,
    YELLOW,
    TEAL,
    PURPLE,
    GREY,
    ORANGE
  }

  enum class VictoryCondition {
    STANDARD,
    CONQUEST,
    TIMELIMIT,
    SCORELIMIT,
    CUSTOM
  };

  enum class GameType {
    RANDOM_MAP,
    REGICIDE,
    DEATH_MATCH,
    SCENARIO,
    CAMPAIGN,
    KING_OF_THE_HILL,
    WONDER_RACE,
    DEFEND_WONDER,
    TURBO_RANDOM_MAP
  };

  enum class MapStyle {
    STANDARD,
    REALWORLD,
    CUSTOM
  };

  enum class DifficultyLevel {
    HARDEST,
    HARD,
    MODERATE,
    STANDARD,
    EASIEST
  };

  enum class GameSpeed {
    SLOW = 100,
    NORMAL = 150,
    FAST = 200
  };

  enum class RevealMap {
    NORMAL,
    EXPLORED,
    ALLVISIBLE
  };

  enum class MapSize {
    TINY,
    SMALL,
    MEDIUM,
    NORMAL,
    LARGE,
    GIANT
  };

  enum class GameVersion {
    UNKNOWN,
    AOK,
    AOKTRIAL,
    AOK20,
    AOK20A,
    AOC,
    AOCTRIAL,
    AOC10,
    AOC10C,
    AOE2HD,
    AOFE21,
    AOFE22,
    AOCUP11,
    AOCUP12,
    AOCUP13,
    AOCUP14
  };

  enum class GameMode {
    SINGLEPLAYER,
    MULTIPLAYER
  };

  enum class GameResult {
    LOSS,
    WIN,
    SURVIVALTOFINISH,
    DISCONNECT
  };

  enum class Resource {
    FOOD,
    WOOD,
    STONE,
    GOLD
  };

struct InitialState {
  struct Position { long x; long y; Position() : x(0), y(0) {} };
  unsigned int food;
  unsigned int wood;
  unsigned int stone;
  unsigned int gold;
  StartingAge startingAge;
  unsigned int houseCapacity;
  unsigned int population;
  unsigned int civilianPop;
  unsigned int militaryPop;
  unsigned int extraPop;
  Position position;
  std::string startingAgeString;
  InitialState() : food(0), wood(0), stone(0), gold(0), startingAge(StartingAge::DARK_AGE),
    houseCapacity(0), population(0), civilianPop(0), militaryPop(0), extraPop(0) {}
};

struct MilitaryStats {
  unsigned int militaryScore;
  unsigned int unitsKilled;
  unsigned int unitsLost;
  unsigned int buildingsRazed;
  unsigned int buildingsLost;
  unsigned int unitsConverted;
  MilitaryStats() : militaryScore(0), unitsKilled(0), unitsLost(0), buildingsRazed(0),
    buildingsLost(0), unitsConverted(0) {}
};

struct EconomyStats {
  unsigned int economyScore;
  unsigned int foodCollected;
  unsigned int woodCollected;
  unsigned int stoneCollected;
  unsigned int goldCollected;
  unsigned int tributeSent;
  unsigned int tributeRcvd;
  unsigned int tradeProfit;
  unsigned int relicGold;
  EconomyStats() : economyScore(0), foodCollected(0), woodCollected(0), stoneCollected(0),
    goldCollected(0), tributeSent(0), tributeRcvd(0), tradeProfit(0), relicGold(0) {}
};

struct TechnologyStats {
  unsigned int technologyScore;
  unsigned int feudalAge;
  unsigned int castleAge;
  unsigned int imperialAge;
  unsigned int mapExplored;
  unsigned int researchCount;
  unsigned int researchPercent;
  TechnologyStats() : technologyScore(0), feudalAge(0), castleAge(0), imperialAge(0),
    mapExplored(0), researchCount(0), researchPercent(0) {}
};

struct SocietyStats {
  unsigned int societyScore;
  unsigned int totalWonders;
  unsigned int totalCastles;
  unsigned int relicsCaptured;
  unsigned int villagerHigh;
  SocietyStats() : societyScore(0), totalWonders(0), totalCastles(0), relicsCaptured(0),
    villagerHigh(0) {}
};

struct Achievement {
  bool victory;
  bool medal;
  GameResult result;
  unsigned int totalScore;
  MilitaryStats militaryStats;
  EconomyStats economyStats;
  TechnologyStats technologyStats;
  SocietyStats societyStats;
  Achievement() : victory(false), medal(false), result(GameResult::LOSS), totalScore(0) {}
};

struct CoopingPlayer {
  std::string name;
  unsigned int resignTime;
  unsigned int disconnectTime;
  CoopingPlayer() : resignTime(0), disconnectTime(0) {}
};

struct Player : CoopingPlayer {
  int index;
  bool human;
  int team;
  bool owner;
  Civilization civId;
  std::string civ;
  PlayerColor color;
  unsigned int feudalTime;
  unsigned int castleTime;
  unsigned int imperialTime;
  std::vector<CoopingPlayer> coopingPlayers;
  InitialState initialState;
  Achievement achievement;
  Player() : index(0), human(false), team(0), owner(false), civId(Civilization::BRITONS),
    color(PlayerColor::UNDEFINED), feudalTime(0), castleTime(0), imperialTime(0) {}
};

struct Victory {
  int timeLimit;
  int scoreLimit;
  VictoryCondition victoryCondition;
  std::string victoryString;
  Victory() : timeLimit(0), scoreLimit(0), victoryCondition(VictoryCondition::STANDARD) {}
};

struct ExtraGameData {
  bool hasData;
  bool allTechs;
  bool allowCheats;
  bool teamTogether;
  bool lockSpeed;
  bool complete;
  ExtraGameData() : hasData(false), allTechs(false), allowCheats(false), teamTogether(false),
    lockSpeed(false), complete(false) {}
};

struct GameSettings {
  GameType gameType;
  MapStyle mapStyle;
  DifficultyLevel difficultyLevel;
  GameSpeed gameSpeed;
  RevealMap revealMap;
  MapSize mapSize;
  std::string map;
  std::string playersType;
  std::string pov;
  std::string objectives;
  int mapId;
  int popLimit;
  bool lockDiplomacy;
  unsigned int playTime;
  bool inGameCoop;
  bool isScenario;
  bool isFFA;
  std::string scenarioFileName;
  GameVersion gameVersion;
  GameMode gameMode;
  Victory victory;
  ExtraGameData extra;
  std::string gameTypeString;
  std::string mapStyleString;
  std::string difficultyLevelString;
  std::string gameSpeedString;
  std::string revealMapString;
  std::string mapSizeString;
  std::string gameVersionString;
  std::string gameSubVersionString;
  GameSettings() : gameType(GameType::RANDOM_MAP), mapStyle(MapStyle::STANDARD),
    difficultyLevel(DifficultyLevel::STANDARD), gameSpeed(GameSpeed::NORMAL),
    revealMap(RevealMap::NORMAL), mapSize(MapSize::NORMAL), mapId(0), popLimit(0),
    lockDiplomacy(false), playTime(0), inGameCoop(false), isScenario(false), isFFA(false),
    gameVersion(GameVersion::UNKNOWN), gameMode(GameMode::SINGLEPLAYER) {}
};

struct ChatMessage {
  unsigned int time;
  std::string msg;
  PlayerColor color;
  ChatMessage() : time(0), color(PlayerColor::UNDEFINED) {}
};

struct Tribute {
  unsigned int time;
  const Player& playerFrom;
  const Player& playerTo;
  Resource resource;
  unsigned int amount;
  float fee;
  Tribute(const Player& playerFrom, const Player& playerTo) : time(0), playerFrom(playerFrom),
    playerTo(playerTo), resource(Resource::FOOD), amount(0), fee(0.0) {}
};

struct Research {
  int id;
  unsigned int time;
  const Player& player;
  std::string name;
  Research(const Player& player) : id(0), time(0), player(player) {}
};

typedef std::map<int, Player> Players;  // player's index to player map
typedef std::map<int, std::reference_wrapper<const Player>> Team; // player's index to player's reference map
typedef std::map<int, Team> Teams;  // team's index to team map

typedef std::pair<int, Player> PlayersPair;
typedef std::pair<int, std::reference_wrapper<const Player>> TeamPair;
typedef std::pair<int, Team> TeamsPair;

typedef std::vector<ChatMessage> ChatMessages;
typedef std::vector<Tribute> Tributes;
typedef std::vector<Research> Researches;

class ERecAnalystException : public std::runtime_error
{
public:
  ERecAnalystException(const std::string& msg) : runtime_error(msg) {}
};

class RecAnalyst {
public:
  RecAnalyst(void);
  ~RecAnalyst(void);
  void analyze(const std::string& fileName);
  void generateMap(int width, int height, std::vector<char>& pngBuffer);
  const GameSettings& gameSettings() const;
  const Players& players() const;
  const Teams& teams() const;
  const ChatMessages& preGameChatMessages() const;
  const ChatMessages& inGameChatMessages() const;
  const Tributes& tributes() const;
  const Researches& researches() const;
  const Players::const_iterator owner() const;
  const Players::const_iterator getPlayer(std::string name, bool canCoop = true) const;
  bool hasPlayer(std::string name, bool canCoop = true) const;
  bool hasAchievements() const;
  int analyzeTime() const;
  static std::string gameTimeToString(unsigned int time);
private:
  class Impl;
  std::unique_ptr<Impl> pimpl;
};

} // namespace

#endif  //_RECANALYSTWRAP_H_
