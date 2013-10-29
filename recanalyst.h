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

#ifndef RECANALYST_H_
#define RECANALYST_H_
#include <Windows.h>

/*
** Make sure we can call this stuff from C++.
*/
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Recanalyst is represented by a pointer to an instance of the structure named
 * "recanalyst". You can think of a recanalyst pointer as an object.
 * The recanalyst_create() is its constructor and recanalyst_free() is its
 * destructor. Other routines are methods on a recanalyst object.
 */
typedef struct recanalyst recanalyst;

/*
 * This structure contains information about an initial state of the player.
 */
typedef struct tagRECANALYST_INITIALSTATE {
  DWORD dwFood;
  DWORD dwWood;
  DWORD dwStone;
  DWORD dwGold;
  DWORD dwStartingAge;
  DWORD dwHouseCapacity;
  DWORD dwPopulation;
  DWORD dwCivilianPop;
  DWORD dwMilitaryPop;
  DWORD dwExtraPop;
  POINT ptPosition;
  TCHAR szStartingAge[256];
} RECANALYST_INITIALSTATE, *LPRECANALYST_INITIALSTATE;

/*
 * This structure contains information about military stats of the player.
 */
typedef struct tagRECANALYST_MILITARYSTATS {
  WORD wMilitaryScore;
  WORD wUnitsKilled;
  WORD wUnitsLost;
  WORD wBuildingsRazed;
  WORD wBuildingsLost;
  WORD wUnitsConverted;
} RECANALYST_MILITARYSTATS, *LPRECANALYST_MILITARYSTATS;

/*
 * This structure contains information about economy stats of the player.
 */
typedef struct tagRECANALYST_ECONOMYSTATS {
  WORD wEconomyScore;
  DWORD dwFoodCollected;
  DWORD dwWoodCollected;
  DWORD dwStoneCollected;
  DWORD dwGoldCollected;
  WORD wTributeSent;
  WORD wTributeRcvd;
  WORD wTradeProfit;
  WORD wRelicGold;
} RECANALYST_ECONOMYSTATS, *LPRECANALYST_ECONOMYSTATS;

/*
 * This structure contains information about technology stats of the player.
 */
typedef struct tagRECANALYST_TECHNOLOGYSTATS {
  WORD wTechnologyScore;
  DWORD dwFeudalAge;
  DWORD dwCastleAge;
  DWORD dwImperialAge;
  BYTE byMapExplored;
  BYTE byResearchCount;
  BYTE byResearchPercent;
} RECANALYST_TECHNOLOGYSTATS, *LPRECANALYST_TECHNOLOGYSTATS;

/*
 * This structure contains information about society stats of the player.
 */
typedef struct tagRECANALYST_SOCIETYSTATS {
  WORD wSocietyScore;
  BYTE byTotalWonders;
  BYTE byTotalCastles;
  BYTE byRelicsCaptured;
  BYTE wVillagerHigh;
} RECANALYST_SOCIETYSTATS, *LPRECANALYST_SOCIETYSTATS;

/*
 * This structure contains information about achievement of the player.
 */
typedef struct tagRECANALYST_ACHIEVEMENT {
  BOOL bVictory;
  BOOL bMedal;
  DWORD dwResult;
  DWORD dwTotalScore;
  LPRECANALYST_MILITARYSTATS lpMilitaryStats;
  LPRECANALYST_ECONOMYSTATS lpEconomyStats;
  LPRECANALYST_TECHNOLOGYSTATS lpTechnologyStats;
  LPRECANALYST_SOCIETYSTATS lpSocietyStats;
} RECANALYST_ACHIEVEMENT, *LPRECANALYST_ACHIEVEMENT;

/*
 * This structure contains information about a player.
 */
typedef struct tagRECANALYST_PLAYER {
  TCHAR szName[256];
  DWORD dwIndex;
  BOOL bHuman;
  DWORD dwTeam;
  BOOL bOwner;
  TCHAR szCivilization[256];
  DWORD dwCivId;
  DWORD dwColor;
  BOOL bIsCooping;
  DWORD dwFeudalTime;
  DWORD dwCastleTime;
  DWORD dwImperialTime;
  DWORD dwResignTime;
  DWORD dwDisconnectTime;
  LPRECANALYST_INITIALSTATE lpInitialState;  // pointer to InitialState struct data
  LPRECANALYST_ACHIEVEMENT lpAchievement;  // pointer to Achievement struct data
} RECANALYST_PLAYER, *LPRECANALYST_PLAYER;

/*
 * This structure contains information about victory settings.
 */
typedef struct tagRECANALYST_VICTORY {
  DWORD dwTimeLimit;
  DWORD dwScoreLimit;
  DWORD dwVictoryCondition;
  TCHAR szVictory[256];
} RECANALYST_VICTORY, *LPRECANALYST_VICTORY;

/*
 * This structure contains information about extra game data.
 */
typedef struct tagRECANALYST_EXTRAGAMEDATA {
  BOOL bHasData;
  BOOL bAllTechs;
  BOOL bAllowCheats;
  BOOL bTeamTogether;
  BOOL bLockSpeed;
  BOOL bComplete;
} RECANALYST_EXTRAGAMEDATA, *LPRECANALYST_EXTRAGAMEDATA;

/*
 * This structure contains information about game settings.
 */
typedef struct tagRECANALYST_GAMESETTINGS {
  DWORD dwGameType;
  DWORD dwMapStyle;
  DWORD dwDifficultyLevel;
  DWORD dwGameSpeed;
  DWORD dwRevealMap;
  DWORD dwMapSize;
  BOOL bIsScenario;
  DWORD dwPlayers;
  DWORD dwPOV;
  DWORD dwMapId;
  DWORD dwPopLimit;
  BOOL bLockDiplomacy;
  DWORD dwPlayTime;
  BOOL bInGameCoop;
  BOOL bIsFFA;
  DWORD dwVersion;
  DWORD dwGameMode;
  TCHAR szMap[65536];
  TCHAR szPlayersType[128];
  TCHAR szPOV[256];
  TCHAR szGameType[256];
  TCHAR szMapStyle[256];
  TCHAR szDifficultyLevel[256];
  TCHAR szGameSpeed[256];
  TCHAR szRevealMap[256];
  TCHAR szMapSize[256];
  TCHAR szVersion[256];
  TCHAR szScFileName[65536];
  TCHAR szSubVersion[256];
  LPRECANALYST_VICTORY lpVictory;
  LPRECANALYST_EXTRAGAMEDATA lpExtra;
} RECANALYST_GAMESETTINGS, *LPRECANALYST_GAMESETTINGS;

/*
 * This structure contains information about a chat message.
 */
typedef struct tagRECANALYST_CHATMESSAGE {
  DWORD dwTime;   // always zero for pre-game chat messages
  DWORD dwColor;  /* zero for players who left the game before its
                     start in pre-game chat; zero for age advances,
                     resign and disconnect messages in in-game chat */
  TCHAR szMessage[256];
} RECANALYST_CHATMESSAGE, *LPRECANALYST_CHATMESSAGE;

/*
 * This structure contains information about a tribute.
 */
typedef struct tagRECANALYST_TRIBUTE {
  DWORD dwTime;
  DWORD dwPlayerFrom;
  DWORD dwPlayerTo;
  BYTE byResource;
  DWORD dwAmount;
  FLOAT fFee;
} RECANALYST_TRIBUTE, *LPRECANALYST_TRIBUTE;

/*
 * This structure contains information about a research.
 */
typedef struct tagRECANALYST_RESEARCH {
  DWORD dwTime;
  DWORD dwId;
  DWORD dwPlayerId;
  TCHAR szName[256];
} RECANALYST_RESEARCH, *LPRECANALYST_RESEARCH;

/*
 * The EnumPlayersProc routine is an application-defined callback function
 * that receives player data in tagRECANALYST_PLAYER structures as a result
 * of a call to the recanalyst_enumplayers() routine.
 *
 * lpPlayer contains player data. See tagRECANALYST_PLAYER structure.
 *
 * lParam specifies the application-defined value given in
 * recanalyst_enumplayers().
 *
 * To continue enumeration, the callback function must return TRUE, to stop
 * enumeration, it must return FALSE.
 */
typedef BOOL (CALLBACK* EnumPlayersProc)(LPRECANALYST_PLAYER lpPlayer,
                                         LPARAM lParam);

/*
 * The EnumChatMessagesProc routine is an application-defined callback function
 * that receives chat message data in tagRECANALYST_CHATMESSAGE structures as
 * a result of a call to the recanalyst_enumpregamechat() or
 * recanalyst_enumingamechat() routines.
 *
 * lpChatMessage contains chat message data. See TChatMessageStruct structure.
 *
 * lParam specifies the application-defined value given in
 * recanalyst_enumpregamechat() or recanalyst_enumingamechat().
 *
 * To continue enumeration, the callback function must return TRUE, to stop
 * enumeration, it must return FALSE.
 */
typedef BOOL (CALLBACK* EnumChatMessagesProc)(
  LPRECANALYST_CHATMESSAGE lpChatMessage, LPARAM lParam);

/*
 * The EnumTributesProc routine is an application-defined callback function
 * that receives tribute data in tagRECANALYST_TRIBUTE structures as a result
 * of a call to the recanalyst_enumtributes() routine.
 *
 * lpTribute contains tribute data. See tagRECANALYST_TRIBUTE structure.
 *
 * lParam specifies the application-defined value given in
 * recanalyst_enumtributes().
 *
 * To continue enumeration, the callback function must return TRUE, to stop
 * enumeration, it must return FALSE.
 */
typedef BOOL (CALLBACK* EnumTributesProc)(LPRECANALYST_TRIBUTE lpTribute,
                                          LPARAM lParam);

/*
 * The EnumResearchesProc routine is an application-defined callback function
 * that receives research data in tagRECANALYST_RESEARCH structures as a result
 * of a call to the recanalyst_enumresearches() routine.
 *
 * lpResearch contains research data. See tagRECANALYST_RESEARCH structure.
 *
 * lParam specifies the application-defined value given in
 * recanalyst_enumresearches().
 *
 * To continue enumeration, the callback function must return TRUE, to stop
 * enumeration, it must return FALSE.
 */
typedef BOOL (CALLBACK* EnumResearchesProc)(LPRECANALYST_RESEARCH lpResearch,
                                            LPARAM lpParam);

/*
 * Return codes.
 */
#define RECANALYST_OK           0	 // Successful result
// analyze error codes
#define RECANALYST_NOFILE      -1  // No file has been specified for analyzing
#define RECANALYST_FILEEXT     -2  // Wrong file extension, file format is not
                                   // supported
#define RECANALYST_EMPTYHEADER -3  // Header length is zero
#define RECANALYST_DECOMP      -4  // Cannot decompress header section
#define RECANALYST_FILEREAD    -5  // Cannot read sections
#define RECANALYST_FILEOPEN    -6  // Cannot open file
#define RECANALYST_UNKNOWN     -7  // Unknown error
#define RECANALYST_HEADLENREAD -8  // Unable to read the header length
#define RECANALYST_NOTRIGG     -9  // "Trigger Info" block has not been found
#define RECANALYST_NOGAMESETS -10  // "Game Settings" block has not been found
#define RECANALYST_READPLAYER -11
//#define RECANALYST_FILECREATE -12  // Cannot create file
//#define RECANALYST_COMP       -13  // Cannot compress header section
// general error codes
#define RECANALYST_GENBASE     RECANALYST_READPLAYER - 1  // {$IFDEF EXTENDED}RECANALYST_COMP - 1{$ELSE}RECANALYST_READPLAYER - 1{$ENDIF};
#define RECANALYST_INVALIDPTR  RECANALYST_GENBASE       // Invalid pointer
#define RECANALYST_FREEOBJ     RECANALYST_GENBASE - 1   // Unable to release object instance
#define RECANALYST_NOCALLBACK  RECANALYST_GENBASE - 2   // Error setting parameters
#define RECANALYST_ENUMP       RECANALYST_GENBASE - 3   // Error enumerating players
#define RECANALYST_ANALYZEF    RECANALYST_GENBASE - 4   // Error analyzing file
#define RECANALYST_NOTANALYZED RECANALYST_GENBASE - 5   // File has not been analyzed yet
#define RECANALYST_TIMECONV    RECANALYST_GENBASE - 6   // Error converting time to its string representation
#define RECANALYST_OBJECTIVES  RECANALYST_GENBASE - 7   // Error getting an objectives string
#define RECANALYST_ENUMPRECHAT RECANALYST_GENBASE - 8
#define RECANALYST_ENUMINCHAT  RECANALYST_GENBASE - 9
#define RECANALYST_ENUMT       RECANALYST_GENBASE - 10
#define RECANALYST_ENUMR       RECANALYST_GENBASE - 11
#define RECANALYST_GAMESETTS   RECANALYST_GENBASE - 12  // Error getting game settings data
#define RECANALYST_GENMAP      RECANALYST_GENBASE - 13  // Error generating map
#define RECANALYST_ANLTIME     RECANALYST_GENBASE - 14
//  {$IFDEF EXTENDED}
//  RECANALYST_GETCOMM     = GEN_BASE - 15;
//  RECANALYST_SETCOMM     = GEN_BASE - 16;
//  {$ENDIF}

/*
 * exported api routines
 */
#define DLLIMPORT __declspec(dllimport)

/*
 * This routine creates a recanalyst object. If the object is created
 * successfully, then its pointer is returned. Otherwise NULL is returned.
 */
DLLIMPORT recanalyst* WINAPI recanalyst_create();

/*
 * This routine is the destructor for the recanalyst object.
 * The parameter to recanalyst_free() must be a recanalyst object obtained
 * from recanalyst_create().
 */
DLLIMPORT int WINAPI recanalyst_free(recanalyst*);

/*
 * This routine analyzes a file set by the lpFileName parameter.
 * recanalyst_analyze() can be called repeatedly on the recanalyst object.
 *
 * lpFileName pointer to ANSI filename string.
 */
DLLIMPORT int WINAPI recanalyst_analyze(recanalyst*, LPCTSTR lpFileName);

/*
 * This routine gets the game settings data. recanalyst_analyze() must first
 * be called.
 *
 * lpGameSettings points to a tagRECANALYST_GAMESETTINGS to receive the game
 *   settings data.
 */
DLLIMPORT int WINAPI recanalyst_getgamesettings(recanalyst*,
  LPRECANALYST_GAMESETTINGS lpGameSettings);

/*
 * This routine enumerates all players by passing the tagRECANALYST_PLAYER of
 * each player, in turn, to an application-defined callback function.
 * recanalyst_enumplayers() continues until the last player is enumerated or
 * the callback function returns FALSE. recanalyst_analyze() must first be
 * called.
 *
 * lpEnumFunc points to an application-defined callback function. For more
 *   information, see EnumPlayersProc callback function.
 *
 * lParam specifies a 32-bit/64-bit, application-defined value to be passed
 *   to the callback function.
 */
DLLIMPORT int WINAPI recanalyst_enumplayers(recanalyst*,
  EnumPlayersProc lpEnumFunc, LPARAM lParam);

/*
 * This routine gets the objectives string. recanalyst_analyze() must first be
 * called.
 *
 * lpObjectives address of buffer for objectives string, you can get the size
 *   of buffer required for objectives string by passing in a NULL parameter.
 */
DLLIMPORT int WINAPI recanalyst_getobjectives(recanalyst*,
  LPTSTR lpObjectives);

/* 
 * This routine enumerates pre-game chat messages by passing the
 * tagRECANALYST_CHATMESSAGE of each message, in turn, to
 * an application-defined callback function. recanalyst_enumpregamechat()
 * continues until the last message is enumerated or the callback function
 * returns FALSE. recanalyst_analyze() must first be called.
 *
 * lpEnumFunc points to an application-defined callback function. For more
 *   information, see EnumChatMessagesProc callback function.
 *
 * lParam specifies a 32-bit/64-bit, application-defined value to be passed
 *   to the callback function.
 */
DLLIMPORT int WINAPI recanalyst_enumpregamechat(recanalyst*,
  EnumChatMessagesProc lpEnumFunc, LPARAM lParam);

/* 
 * This routine enumerates in-game chat messages by passing the
 * tagRECANALYST_CHATMESSAGE of each message, in turn, to
 * an application-defined callback function. recanalyst_enumingamechat()
 * continues until the last message is enumerated or the callback function
 * returns FALSE. recanalyst_analyze() must first be called.
 *
 * lpEnumFunc points to an application-defined callback function. For more
 *   information, see EnumChatMessagesProc callback function.
 *
 * lParam specifies a 32-bit/64-bit, application-defined value to be passed
 *   to the callback function.
 */
DLLIMPORT int WINAPI recanalyst_enumingamechat(recanalyst*,
  EnumChatMessagesProc lpEnumFunc, LPARAM lParam);

/*
 * This routine enumerates tributes by passing the tagRECANALYST_TRIBUTE
 * of each tribute, in turn, to an application-defined callback function.
 * recanalyst_enumtributes() continues until the last tribute is enumerated or
 * the callback function returns FALSE. recanalyst_analyze() must first be
 * called.
 *
 * lpEnumFunc points to an application-defined callback function. For more
 *   information, see EnumTributesProc callback function.
 *
 * lParam specifies a 32-bit/64-bit, application-defined value to be passed
 *   to the callback function.
 */
DLLIMPORT int WINAPI recanalyst_enumtributes(recanalyst*,
  EnumTributesProc lpEnumFunc, LPARAM lParam);

/* 
 * This routine enumerates researches by passing the tagRECANALYST_RESEARCH
 * of each research, in turn, to an application-defined callback function.
 * recanalyst_enumresearches() continues until the last research is enumerated
 * or the callback function returns  FALSE. recanalyst_analyze() must first be
 * called.
 *
 * lpEnumFunc points to an application-defined callback function. For more
 *   information, see EnumResearchesProc callback function.
 *
 * lParam specifies a 32-bit/64-bit, application-defined value to be passed
 *   to the callback function.
 */
DLLIMPORT int WINAPI recanalyst_enumresearches(recanalyst*,
  EnumResearchesProc lpEnumFunc, LPARAM lParam);

/*
 * This routine generates a map image. recanalyst_analyze() must first be
 * called.
 *
 * dwWidth defines the map image width.
 *
 * dwHeight defines the map image height.
 *
 * lpImageBuffer address of buffer for map image, you can get the size
 *   of buffer required for map image by passing in a NULL parameter.
 */
DLLIMPORT int WINAPI recanalyst_generatemap(recanalyst*, DWORD dwWidth,
  DWORD dwHeight, CHAR* lpImageBuffer);

/*
 * This routine gets the analyze time in miliseconds.
 * recanalyst_analyze() must first be called.
 */
DLLIMPORT int WINAPI recanalyst_analyzetime(recanalyst*);

/*
 * This routine converts internal time representation into a string that
 * represents its value.
 *
 * dwTime internal time representation (miliseconds).
 *
 * lpTime address of buffer for time string, you can get the size of buffer
 *   required for time string by passing in a NULL parameter.
 */
DLLIMPORT int WINAPI recanalyst_timetostring(DWORD dwTime, LPTSTR lpTime);

/*
 * This routine can be used to obtain an English language description
 * of the error code defined by iErrCode parameter.
 */
DLLIMPORT LPCTSTR WINAPI recanalyst_errmsg(int iErrCode);

/*
 * This routine returns the version of the recanalyst library.
 */
DLLIMPORT LPCTSTR WINAPI recanalyst_libversion();

#ifdef __cplusplus
}  /* End of the 'extern "C"' block */
#endif
#endif /* RECANALYST_H_ */
