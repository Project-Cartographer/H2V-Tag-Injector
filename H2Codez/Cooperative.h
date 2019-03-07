#include "stdafx.h"



class Cooperative
{
public :
    DWORD Difficulty;    //DifficultyLevel
    DWORD GameType;      //GameTypeIndex
    DWORD GameTypeUI;    //GameTypeUIIndex
	DWORD CoopSpawns;    //CoopSpawn
	DWORD GameEngine;    //GameEngine(SP/MP/MM)
	DWORD PauseGame;     //Pause Game <-To fix the pause of game When Host Presses Escape
	DWORD StausCheck;    //Check User Status(Ingame/Lobby etc..)
	BYTE CoopBiped;      //To Decide Ingame Biped for Coop(MC/Dervish)
	BYTE CoopTeam;       //To Decide Ingame Team for Coop(Humans/Elites)
	DWORD PlayerCount;   //Check Players Ingame



    BOOL MPGame;        //IsGameMP
    BOOL CoopGame;      //IsGameCoop
    BOOL LoadPCR;       //LoadPCR
	BOOL Client_f;      //To Check if Client Fixes are done
	BOOL Host_f;        //To Check if Host Fixes are done
	BOOL Host_L;        //Starts Stops Host Loop
	BOOL Begin;
    
};

extern Cooperative Coop;

#pragma region Declarations
int GetPlayerDyanamic(int Index);
int GetPlayersAlive();
bool GetPlayersAlive(int index);
bool IsHost();
void _cdecl call_SpawnPlayer(int PlayerIndex);
char call_RestartLevel();
void SpawnAICharacters();
void HostHooks();
void Fixes();
void ClientHooks();
void TempUnHook();
void MapThings();
void SpawnPlayersCoop(); 

#pragma endregion


bool IsHost();

int __cdecl h_GameEngineSet(void* pEngine);

char __fastcall h_Crashy001(void *This, void* rubbish, int a2, int a3, int a4, int a5);

int __cdecl h_FpWeaponsSet(int PlayerIndex, int UnitDatum, int PlayerModel);

void _cdecl h_SpawnPlayer(int PlayerIndex);



signed int Test();
//Assign Halo 2 Pointers
void CoopAssignPointers();
//MapChecks
void MapThings();

//Start Cooperative Hooks (For Both Host/Client)
void CooperativeHook();


//Remove All Cooperative Hooks
void CooperativeUnHook();
//Remove Temporary Coopearative Hooks(To stop Glitches/Bugs)
void TempUnHook();

void Fixes();

void InitializeCoop();
