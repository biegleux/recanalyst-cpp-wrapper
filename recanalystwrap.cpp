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

#include <algorithm>
#include <functional>
#include "recanalystwrap.h"

namespace RecAnalystWrapper {

class RecAnalystTranslator {
public:
  static void translateInitialState(const RECANALYST_INITIALSTATE& is, InitialState& initialState);
  static void translateMilitaryStats(const RECANALYST_MILITARYSTATS& ms, MilitaryStats& militaryStats);
  static void translateEconomyStats(const RECANALYST_ECONOMYSTATS& es, EconomyStats& economyStats);
  static void translateTechnologyStats(const RECANALYST_TECHNOLOGYSTATS& ts, TechnologyStats& technologyStats);
  static void translateSocietyStats(const RECANALYST_SOCIETYSTATS& ss, SocietyStats& societyStats);
  static void translateAchievement(const RECANALYST_ACHIEVEMENT& a, Achievement& achievement);
  static void translateCoopingPlayer(const RECANALYST_PLAYER& p, CoopingPlayer& player);
  static void translatePlayer(const RECANALYST_PLAYER& p, Player& player);
  static void translateVictory(const RECANALYST_VICTORY& v, Victory& victory);
  static void translateExtraGameData(const RECANALYST_EXTRAGAMEDATA& e, ExtraGameData& extra);
  static void translateGameSettings(const RECANALYST_GAMESETTINGS& gs, GameSettings& gameSettings);
  static void translateChatMessage(const RECANALYST_CHATMESSAGE& cm, ChatMessage& chatMessage);
  static Tribute translateTribute(const RECANALYST_TRIBUTE& t, const Players& players);
  static Research translateResearch(const RECANALYST_RESEARCH& r, const Players& players);
};

void RecAnalystTranslator::translateInitialState(const RECANALYST_INITIALSTATE& is, InitialState& initialState) {
  initialState.food = is.dwFood;
  initialState.wood = is.dwWood;
  initialState.stone = is.dwStone;
  initialState.gold = is.dwGold;
  initialState.startingAge = static_cast<StartingAge>(is.dwStartingAge);
  initialState.houseCapacity = is.dwHouseCapacity;
  initialState.population = is.dwPopulation;
  initialState.civilianPop = is.dwCivilianPop;
  initialState.militaryPop = is.dwMilitaryPop;
  initialState.extraPop = is.dwExtraPop;
  initialState.position.x = is.ptPosition.x;
  initialState.position.y = is.ptPosition.y;
  initialState.startingAgeString = is.szStartingAge;
}

void RecAnalystTranslator::translateMilitaryStats(const RECANALYST_MILITARYSTATS& ms, MilitaryStats& militaryStats) {
  militaryStats.militaryScore = ms.wMilitaryScore;
  militaryStats.unitsKilled = ms.wUnitsKilled;
  militaryStats.unitsLost = ms.wUnitsLost;
  militaryStats.buildingsRazed = ms.wBuildingsRazed;
  militaryStats.buildingsLost = ms.wBuildingsLost;
  militaryStats.unitsConverted = ms.wUnitsConverted;
}

void RecAnalystTranslator::translateEconomyStats(const RECANALYST_ECONOMYSTATS& es, EconomyStats& economyStats) {
  economyStats.economyScore = es.wEconomyScore;
  economyStats.foodCollected = es.dwFoodCollected;
  economyStats.woodCollected = es.dwWoodCollected;
  economyStats.stoneCollected = es.dwStoneCollected;
  economyStats.goldCollected = es.dwGoldCollected;
  economyStats.tributeSent = es.wTributeSent;
  economyStats.tributeRcvd = es.wTributeRcvd;
  economyStats.tradeProfit = es.wTradeProfit;
  economyStats.relicGold = es.wRelicGold;
}

void RecAnalystTranslator::translateTechnologyStats(const RECANALYST_TECHNOLOGYSTATS& ts, TechnologyStats& technologyStats) {
  technologyStats.technologyScore = ts.wTechnologyScore;
  technologyStats.feudalAge = ts.dwFeudalAge;
  technologyStats.castleAge = ts.dwCastleAge;
  technologyStats.imperialAge = ts.dwImperialAge;
  technologyStats.mapExplored = ts.byMapExplored;
  technologyStats.researchCount = ts.byResearchCount;
  technologyStats.researchPercent = ts.byResearchPercent;
}

void RecAnalystTranslator::translateSocietyStats(const RECANALYST_SOCIETYSTATS& ss, SocietyStats& societyStats) {
  societyStats.societyScore = ss.wSocietyScore;
  societyStats.totalWonders = ss.byTotalWonders;
  societyStats.totalCastles = ss.byTotalCastles;
  societyStats.relicsCaptured = ss.byRelicsCaptured;
  societyStats.villagerHigh = ss.wVillagerHigh;
}

void RecAnalystTranslator::translateAchievement(const RECANALYST_ACHIEVEMENT& a, Achievement& achievement) {
  achievement.victory = a.bVictory != 0;
  achievement.medal = a.bMedal != 0;
  achievement.result = static_cast<GameResult>(a.dwResult);
  achievement.totalScore = a.dwTotalScore;
  if (a.lpMilitaryStats != NULL) {
    RecAnalystTranslator::translateMilitaryStats(*a.lpMilitaryStats, achievement.militaryStats);
  }
  if (a.lpEconomyStats != NULL) {
    RecAnalystTranslator::translateEconomyStats(*a.lpEconomyStats, achievement.economyStats);
  }
  if (a.lpTechnologyStats != NULL) {
    RecAnalystTranslator::translateTechnologyStats(*a.lpTechnologyStats, achievement.technologyStats);
  }
  if (a.lpSocietyStats != NULL) {
    RecAnalystTranslator::translateSocietyStats(*a.lpSocietyStats, achievement.societyStats);
  }
}

void RecAnalystTranslator::translateCoopingPlayer(const RECANALYST_PLAYER& p, CoopingPlayer& player) {
  player.name = p.szName;
  player.resignTime = p.dwResignTime;
  player.disconnectTime = p.dwDisconnectTime;
}

void RecAnalystTranslator::translatePlayer(const RECANALYST_PLAYER& p, Player& player) {
  RecAnalystTranslator::translateCoopingPlayer(p, player);
  player.index = p.dwIndex;
  player.human = p.bHuman != 0;
  player.team = p.dwTeam;
  player.owner = p.bOwner != 0;
  player.civId = static_cast<Civilization>(p.dwCivId);
  player.civ = p.szCivilization;
  player.color = p.byColor;
  player.feudalTime = p.dwFeudalTime;
  player.castleTime = p.dwCastleTime;
  player.imperialTime = p.dwImperialTime;
  if (p.lpInitialState != NULL) {
    RecAnalystTranslator::translateInitialState(*p.lpInitialState, player.initialState);
  }
  if (p.lpAchievement != NULL) {
    RecAnalystTranslator::translateAchievement(*p.lpAchievement, player.achievement);
  }
}

void RecAnalystTranslator::translateVictory(const RECANALYST_VICTORY& v, Victory& victory) {
  victory.timeLimit = v.dwTimeLimit;
  victory.scoreLimit = v.dwScoreLimit;
  victory.victoryCondition = static_cast<VictoryCondition>(v.dwVictoryCondition);
  victory.victoryString = v.szVictory;
}

void RecAnalystTranslator::translateExtraGameData(const RECANALYST_EXTRAGAMEDATA& e, ExtraGameData& extra) {
  extra.hasData = e.bHasData != 0;
  extra.allTechs = e.bAllTechs != 0;
  extra.allowCheats = e.bAllowCheats != 0;
  extra.teamTogether = e.bTeamTogether != 0;
  extra.lockSpeed = e.bLockSpeed != 0;
  extra.complete = e.bComplete != 0;
}

void RecAnalystTranslator::translateGameSettings(const RECANALYST_GAMESETTINGS& gs, GameSettings& gameSettings) {
  gameSettings.gameType = static_cast<GameType>(gs.dwGameType);
  gameSettings.mapStyle = static_cast<MapStyle>(gs.dwMapStyle);
  gameSettings.difficultyLevel = static_cast<DifficultyLevel>(gs.dwDifficultyLevel);
  gameSettings.gameSpeed = static_cast<GameSpeed>(gs.dwGameSpeed);
  gameSettings.revealMap = static_cast<RevealMap>(gs.dwRevealMap);
  gameSettings.mapSize = static_cast<MapSize>(gs.dwMapSize);
  gameSettings.isScenario = gs.bIsScenario != 0;
  gameSettings.mapId = gs.dwMapId;
  gameSettings.popLimit = gs.dwPopLimit;
  gameSettings.lockDiplomacy = gs.bLockDiplomacy != 0;
  gameSettings.playTime = gs.dwPlayTime;
  gameSettings.inGameCoop = gs.bInGameCoop != 0;
  gameSettings.isFFA = gs.bIsFFA != 0;
  gameSettings.gameVersion = static_cast<GameVersion>(gs.dwVersion);
  gameSettings.gameMode = static_cast<GameMode>(gs.dwGameMode);
  gameSettings.map = gs.szMap;
  gameSettings.playersType = gs.szPlayersType;
  gameSettings.pov = gs.szPOV;
  gameSettings.gameTypeString = gs.szGameType;
  gameSettings.mapStyleString = gs.szMapStyle;
  gameSettings.difficultyLevelString = gs.szDifficultyLevel;
  gameSettings.gameSpeedString = gs.szGameSpeed;
  gameSettings.revealMapString = gs.szRevealMap;
  gameSettings.mapSizeString = gs.szMapSize;
  gameSettings.gameVersionString = gs.szVersion;
  gameSettings.scenarioFileName = gs.szScFileName;
  gameSettings.gameSubVersionString = gs.szSubVersion;
  if (gs.lpVictory != NULL) {
    RecAnalystTranslator::translateVictory(*gs.lpVictory, gameSettings.victory);
  }
  if (gs.lpExtra != NULL) {
    RecAnalystTranslator::translateExtraGameData(*gs.lpExtra, gameSettings.extra);
  }
}

void RecAnalystTranslator::translateChatMessage(const RECANALYST_CHATMESSAGE& cm, ChatMessage& chatMessage) {
  chatMessage.time = cm.dwTime;
  chatMessage.msg = cm.szMessage;
  chatMessage.color = cm.byColor;
}

Tribute RecAnalystTranslator::translateTribute(const RECANALYST_TRIBUTE& t, const Players& players) {
  const Player& p1 = players.find(t.dwPlayerFrom)->second;
  const Player& p2 = players.find(t.dwPlayerTo)->second;
  Tribute tribute(p1, p2);
  tribute.time = t.dwTime;
  tribute.resource = static_cast<Resource>(t.byResourceId);
  tribute.amount = t.dwAmount;
  tribute.fee = t.fFee;
  return tribute;
}

Research RecAnalystTranslator::translateResearch(const RECANALYST_RESEARCH& r, const Players& players) {
  const Player& p = players.find(r.dwPlayerId)->second;
  Research research(p);
  research.id = r.dwId;
  research.time = r.dwTime;
  research.name = r.szName;
  return research;
}

class RecAnalyst::Impl
{
public:
  recanalyst* mRecAnalyst;
  Players mPlayers;
  Teams mTeams;
  GameSettings mGameSettings;
  ChatMessages mPreGameChatMessages;
  ChatMessages mInGameChatMessages;
  Tributes mTributes;
  Researches mResearches;
  int mAnalyzeTime;
  void throwExceptionIfError(int code);
  void assignPlayerWithTeam(const Player& player);
  bool enumPlayersCallback(LPRECANALYST_PLAYER lpPlayer);
  bool enumPreGameChatMessagesCallback(LPRECANALYST_CHATMESSAGE lpChatMessage);
  bool enumInGameChatMessagesCallback(LPRECANALYST_CHATMESSAGE lpChatMessage);
  bool enumTributesCallback(LPRECANALYST_TRIBUTE lpTribute);
  bool enumResearchesCallback(LPRECANALYST_RESEARCH lpResearch);
  static BOOL CALLBACK enumPlayersCallback(LPRECANALYST_PLAYER lpPlayer, LPARAM lParam);
  static BOOL CALLBACK enumPreGameChatMessagesCallback(LPRECANALYST_CHATMESSAGE lpChatMessage, LPARAM lParam);
  static BOOL CALLBACK enumInGameChatMessagesCallback(LPRECANALYST_CHATMESSAGE lpChatMessage, LPARAM lParam);
  static BOOL CALLBACK enumTributesCallback(LPRECANALYST_TRIBUTE lpTribute, LPARAM lParam);
  static BOOL CALLBACK enumResearchesCallback(LPRECANALYST_RESEARCH lpResearch, LPARAM lParam);
  static bool isOwner(const PlayersPair& pp);
public:
  Impl(void);
  ~Impl(void);
  void analyze(const std::string& fileName);
  void generateMap(int width, int height, std::vector<char>& pngBuffer);
};

RecAnalyst::Impl::Impl() {
  mAnalyzeTime = 0;
  if ((mRecAnalyst = recanalyst_create()) == NULL) {
    throw ERecAnalystException("Unable to create RecAnalyst object.");
  }
}

RecAnalyst::Impl::~Impl() {
  if (mRecAnalyst != NULL) {
    recanalyst_free(mRecAnalyst);
  }
}

void RecAnalyst::Impl::assignPlayerWithTeam(const Player& player) {
  auto& it = mTeams.find(player.team);
  if (it != mTeams.end()) {
    it->second.insert(TeamPair(player.index, std::cref(player)));
  } else {
    Team team;
    team.insert(TeamPair(player.index, std::cref(player)));
    mTeams.insert(TeamsPair(player.team, team));
  }
}

bool RecAnalyst::Impl::enumPlayersCallback(LPRECANALYST_PLAYER lpPlayer) {
  if (lpPlayer->bIsCooping) {
    CoopingPlayer cplayer;
    RecAnalystTranslator::translateCoopingPlayer(*lpPlayer, cplayer);
    auto& pit = mPlayers.find(lpPlayer->dwIndex);
    pit->second.coopingPlayers.push_back(cplayer); // player already exists, can't point to mPlayers.end()
  } else {
      Player player;
      RecAnalystTranslator::translatePlayer(*lpPlayer, player);
      if (player.team == 0) {
        const auto& iter = mTeams.crbegin();
        player.team = (iter != mTeams.crend()) ? iter->first + 1 : 5;  // max(dwTeam) = 4
      }
      auto& pit = mPlayers.insert(PlayersPair(player.index, player));
      assignPlayerWithTeam(pit.first->second);
  }
  return true;
}

bool RecAnalyst::Impl::enumPreGameChatMessagesCallback(LPRECANALYST_CHATMESSAGE lpChatMessage) {
  ChatMessage chatMessage;
  RecAnalystTranslator::translateChatMessage(*lpChatMessage, chatMessage);
  mPreGameChatMessages.push_back(chatMessage);
  return true;
}

bool RecAnalyst::Impl::enumInGameChatMessagesCallback(LPRECANALYST_CHATMESSAGE lpChatMessage) {
  ChatMessage chatMessage;
  RecAnalystTranslator::translateChatMessage(*lpChatMessage, chatMessage);
  mInGameChatMessages.push_back(chatMessage);
  return true;
}

bool RecAnalyst::Impl::enumTributesCallback(LPRECANALYST_TRIBUTE lpTribute) {
  Tribute& t = RecAnalystTranslator::translateTribute(*lpTribute, mPlayers);
  mTributes.push_back(t);
  return true;
}

bool RecAnalyst::Impl::enumResearchesCallback(LPRECANALYST_RESEARCH lpResearch) {
  Research& r = RecAnalystTranslator::translateResearch(*lpResearch, mPlayers);
  mResearches.push_back(r);
  return true;
}

BOOL CALLBACK RecAnalyst::Impl::enumPlayersCallback(LPRECANALYST_PLAYER lpPlayer, LPARAM lParam) {
  RecAnalyst::Impl* recAnalyst = reinterpret_cast<RecAnalyst::Impl*>(lParam);
  return recAnalyst->enumPlayersCallback(lpPlayer);
}

BOOL CALLBACK RecAnalyst::Impl::enumPreGameChatMessagesCallback(LPRECANALYST_CHATMESSAGE lpChatMessage, LPARAM lParam) {
  RecAnalyst::Impl* recAnalyst = reinterpret_cast<RecAnalyst::Impl*>(lParam);
  return recAnalyst->enumPreGameChatMessagesCallback(lpChatMessage);
}

BOOL CALLBACK RecAnalyst::Impl::enumInGameChatMessagesCallback(LPRECANALYST_CHATMESSAGE lpChatMessage, LPARAM lParam) {
  RecAnalyst::Impl* recAnalyst = reinterpret_cast<RecAnalyst::Impl*>(lParam);
  return recAnalyst->enumInGameChatMessagesCallback(lpChatMessage);
}

BOOL CALLBACK RecAnalyst::Impl::enumTributesCallback(LPRECANALYST_TRIBUTE lpTribute, LPARAM lParam) {
  RecAnalyst::Impl* recAnalyst = reinterpret_cast<RecAnalyst::Impl*>(lParam);
  return recAnalyst->enumTributesCallback(lpTribute);
}

BOOL CALLBACK RecAnalyst::Impl::enumResearchesCallback(LPRECANALYST_RESEARCH lpResearch, LPARAM lParam) {
  RecAnalyst::Impl* recAnalyst = reinterpret_cast<RecAnalyst::Impl*>(lParam);
  return recAnalyst->enumResearchesCallback(lpResearch);
}

void RecAnalyst::Impl::analyze(const std::string& fileName) {
  throwExceptionIfError(recanalyst_analyze(mRecAnalyst, fileName.c_str()));
  RECANALYST_GAMESETTINGS gs;
  RECANALYST_VICTORY v;
  RECANALYST_EXTRAGAMEDATA e;
  gs.lpVictory = &v;
  gs.lpExtra = &e;
  throwExceptionIfError(recanalyst_getgamesettings(mRecAnalyst, &gs));
  RecAnalystTranslator::translateGameSettings(gs, mGameSettings);

  int size = recanalyst_getobjectives(mRecAnalyst, NULL);
  throwExceptionIfError(size);
  if (size > 0) {
    mGameSettings.objectivesString.resize(size);
    throwExceptionIfError(recanalyst_getobjectives(mRecAnalyst, &mGameSettings.objectivesString[0]));
    mGameSettings.objectivesString.resize(size - 1);
  }
  throwExceptionIfError(recanalyst_enumplayers(mRecAnalyst, enumPlayersCallback, reinterpret_cast<LPARAM>(this)));

  throwExceptionIfError(recanalyst_enumpregamechat(mRecAnalyst, enumPreGameChatMessagesCallback, reinterpret_cast<LPARAM>(this)));
  throwExceptionIfError(recanalyst_enumingamechat(mRecAnalyst, enumInGameChatMessagesCallback, reinterpret_cast<LPARAM>(this)));
  throwExceptionIfError(recanalyst_enumtributes(mRecAnalyst, enumTributesCallback, reinterpret_cast<LPARAM>(this)));
  throwExceptionIfError(recanalyst_enumresearches(mRecAnalyst, enumResearchesCallback, reinterpret_cast<LPARAM>(this)));

  int time = recanalyst_analyzetime(mRecAnalyst);
  throwExceptionIfError(time);
  mAnalyzeTime = time;
}

void RecAnalyst::Impl::generateMap(int width, int height, std::vector<char>& pngBuffer) {
  int size = recanalyst_generatemap(mRecAnalyst, width, height, NULL);
  throwExceptionIfError(size);
  pngBuffer.clear();
  pngBuffer.resize(size);
  throwExceptionIfError(recanalyst_generatemap(mRecAnalyst, width, height, pngBuffer.data()));
}

void RecAnalyst::Impl::throwExceptionIfError(int code) {
  if (code < RECANALYST_OK) {
    throw ERecAnalystException(recanalyst_errmsg(code));
  }
}

RecAnalyst::RecAnalyst() : pimpl(new Impl()) {}

RecAnalyst::~RecAnalyst() {}

void RecAnalyst::analyze(const std::string& fileName) {
  return pimpl->analyze(fileName);
}
void RecAnalyst::generateMap(int width, int height, std::vector<CHAR>& pngBuffer) {
  return pimpl->generateMap(width, height, pngBuffer);
}

const GameSettings& RecAnalyst::gameSettings() const {
  return pimpl->mGameSettings;
}

const Players& RecAnalyst::players() const {
  return pimpl->mPlayers;
}

const Teams& RecAnalyst::teams() const {
  return pimpl->mTeams;
}

const ChatMessages& RecAnalyst::preGameChatMessages() const {
  return pimpl->mPreGameChatMessages;
}

const ChatMessages& RecAnalyst::inGameChatMessages() const {
  return pimpl->mInGameChatMessages;
}

const Tributes& RecAnalyst::tributes() const {
  return pimpl->mTributes;
}

const Researches& RecAnalyst::researches() const {
  return pimpl->mResearches;
}

bool RecAnalyst::Impl::isOwner(const PlayersPair& pp) {
  return pp.second.owner;
}

const Players::const_iterator RecAnalyst::owner() const {
  return std::find_if(pimpl->mPlayers.cbegin(), pimpl->mPlayers.cend(), Impl::isOwner);
}

const Players::const_iterator RecAnalyst::getPlayer(std::string name, bool canCoop) const {
  struct {
    const std::string& name;
    bool canCoop;
    auto operator()(const PlayersPair& pp) -> bool {
      const Player& p = pp.second;
      const std::string& playerName = name;
      return p.name == name ||
        (canCoop && (p.coopingPlayers.cend() != std::find_if(p.coopingPlayers.cbegin(),
        p.coopingPlayers.cend(), [&playerName] (const CoopingPlayer& cp) { return cp.name == playerName; })));
      }
  } lambda = {name, canCoop};

  return std::find_if(pimpl->mPlayers.cbegin(), pimpl->mPlayers.cend(), lambda);
}

bool RecAnalyst::hasPlayer(std::string name, bool canCoop) const {
  return getPlayer(name, canCoop) != pimpl->mPlayers.cend();
}

bool RecAnalyst::hasAchievements() const {
  return pimpl->mGameSettings.extra.hasData;
}

int RecAnalyst::analyzeTime() const {
  return pimpl->mAnalyzeTime;
}

std::string RecAnalyst::gameTimeToString(unsigned int time) {
  int size = recanalyst_timetostring(time, NULL);
  if (size <= RECANALYST_OK) {
    return "";
  }
  std::string result(size, '\0');
  recanalyst_timetostring(time, &result[0]);
  result.resize(size - 1);
  return result;
}

} // namespace
