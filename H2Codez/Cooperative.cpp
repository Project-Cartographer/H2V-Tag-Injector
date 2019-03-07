#include "Cooperative.h"
#include "stdafx.h"



#pragma region Functions

typedef int(__cdecl *GameSet)(void*);
GameSet pGameSet;

typedef char(__thiscall *Crashy)(void *, int, int, int, int);
Crashy pCrashy001;///Function at which Game usually Crashes <-someone plz Fix this

typedef int(__cdecl * Fp)(int, int, int);
Fp pFp; //Now Obsolete

typedef void(__cdecl * Spawn)(int);
Spawn pSpawn;

char* GameGlobalsCacheData = new char[0x1188u];

int GetPlayerDyanamic(int Index)
{
	int dyanamic=0;
	int playerdatum=halo.get_unit_datum_from_player_index(Index);
	if (playerdatum != -1)
    dyanamic = *(DWORD *)(*(DWORD *)(0x3003CEF0 + 68) + 12 * (unsigned __int16)playerdatum + 8);
	return dyanamic;
}
int GetObjectDyanamic(DWORD datum)
{
	if(datum!=-1)
	return
		*(DWORD *)(*(DWORD *)(0x3003CEF0 + 68) + 12 * (unsigned __int16)datum + 8);

	return -1;

}


int GetPlayersAlive()
{
	int pcount=0;
	for(int i=0;i<15;i++)
	{
		if (GetPlayerDyanamic(i) != 0)
		{
			if (*(BYTE*)(GetPlayerDyanamic(i) + 0x3F4) == 0x1)
				pcount++;
		}		

	}
	return pcount;
}

bool GetPlayersAlive(int index)
{
	bool pcount=false;
	if (GetPlayerDyanamic(index) != 0)
		if(*(BYTE*)(GetPlayerDyanamic(index)+0x3F4)==0x1)
			pcount=true;

	
	return pcount;
}



void _cdecl call_SpawnPlayer(int PlayerIndex)
{
	typedef void(__cdecl * Spawn)(int);
	Spawn pSpawn = (Spawn)(((char*)game.GetBase()) + 0x55952);
	pSpawn(PlayerIndex);
}

char call_RestartLevel()
{
	typedef char(__cdecl * Rest)();
	Rest pRest = (Rest)(((char*)game.GetBase()) + 0x23E6BC);
	return pRest();
}

void SpawnAICharacters()
{
	//Run this Only on The Great Journey
	char* sObject = new char[0x50];
	DWORD dwBack;
	VirtualProtect(sObject, 0x50, PAGE_EXECUTE_READWRITE, &dwBack);

	game.call_CharacterInitialize(sObject);
	// int choice = rand()%5;

	*(float*)(sObject + 0x4) = *(float*)(((char*)game.GetBase()) + 0x4A8504); //x
	*(float*)(sObject + 0x8) = *(float*)(((char*)game.GetBase()) + 0x4A8508);//y
	*(float*)(sObject + 0xC) = (*(float*)(((char*)game.GetBase()) + 0x4A850C) + 1.0f);//z

																					  //game.CreateCharacter(0xEE130C9D, 0xFF, mya3);
	game.call_CreateCharacter(0x3BA6, 0x0, sObject);

	delete[] sObject;

	//game.call_CreateCharacter(0xFAB5192F, 0x15, sObject);
	//delete[0x50]sObject;
}

bool IsHost()
{
	if (halo.H2Type = H2Server)
		return true;

	int LB = (int)*(int*)((char*)game.GetBase() + 0x420FE8);
	int HID = *(int*)(LB + 0x125C);
	int LID = *(int*)((char*)game.GetBase() + 0x51A629);

	if (*(BYTE*)Coop.StausCheck>0)
	{
		if (LID == HID)
			return true;
		else
			return false;
	}
	else
		return false;
}

int __cdecl h_GameEngineSet(void* pEngine)
{

	pLog.WriteLog("Hooks:: EngineMode (%X)", *(int*)pEngine);
	if (Coop.CoopGame)
	{
		*(BYTE*)pEngine = 1;                       //Changing Engine Pointer to 1
		*(BYTE*)((int)pEngine + 0x2A4 - 8) = 1;    //Changing Coop Pointer to 1
		*(BYTE*)((int)pEngine + 0x2A8 - 8) = 0;    //Changing Some Check to 0
		*(BYTE*)((int)pEngine + 0x2EC - 8) = 0;    //Changing GameType Pointer to 0(SP)
		pLog.WriteLog("Starting Cooperative GamePlay.");
		Coop.CoopGame = false;
		/*	pLog.WriteLog("GameGlobalsCacheData %X", *GameGlobalsCacheData);
		if (*GameGlobalsCacheData==0xFFFFFFCD)
		{
		memcpy(GameGlobalsCacheData, pEngine, 0x1188u);
		pLog.WriteLog("Cache Data Saved in Memory");

		ofstream myfile;
		myfile.open("CoopCacheData.cache",ios::binary);
		myfile.write(GameGlobalsCacheData, 0x1188u);

		myfile.close();
		}
		else
		{
		memcpy(pEngine, GameGlobalsCacheData, 0x1188u);
		pLog.WriteLog("Loaded Saved Cache Data");
		}*/

	}


	/*
	pLog.WriteLog("Hooks:: EngineMode (%i)",*(int*)vpointer);
	MapThings();
	if(Coop.CoopGame==TRUE)
	{

	*(int*)vpointer=1;//Engine Pointer Set to Single Player

	pLog.WriteLog("Coop:: Starting Cooperative Gameplay.");
	pLog.WriteLog("Hooks:: NewEngineMode (%i)",*(int*)vpointer);
	Coop.Host_f = FALSE;
	Coop.CoopGame=FALSE;
	int p=pGameSet(vpointer);
	Fixes();
	return p;
	}
	else
	{
	Coop.Host_L=FALSE;
	Coop.Client_f=FALSE;
	Coop.Host_f=FALSE;
	Coop.Begin = FALSE;
	TempUnHook();
	return pGameSet(vpointer);

	}

	*/

	return pGameSet(pEngine);
}
char __fastcall h_Crashy001(void *This, void* rubbish, int a2, int a3, int a4, int a5)
{


	int myv5 = *(DWORD *)(a2 + 8);
	// int mycrashy= (*(DWORD *)(*(DWORD *)(0x3003CEF0 + 68) + 12 * (unsigned __int16)myv5 + 8) + 0xAA);

	int DA = *(DWORD *)(0x3003CEF0 + 68) + 12 * (unsigned __int16)myv5 + 8;

	//if(Coop.CoopGame==TRUE)
	//*(BYTE*)mycrashy=1;
	if (DA != 0)
	{
		return pCrashy001(This, a2, a3, a4, a5);
	}
	else return 0;


}
int __cdecl h_FpWeaponsSet(int PlayerIndex, int UnitDatum, int PlayerModel)
{
	//PlayerModel = Coop.CoopBiped;
	//*(int*)(0x30002BA0 + (PlayerIndex * 0x204)) = Coop.CoopBiped;
	//*(int*)(0x30002BD8 + (PlayerIndex * 0x204)) = Coop.CoopTeam;
	return pFp(PlayerIndex, UnitDatum, PlayerModel);
}
void _cdecl h_SpawnPlayer(int PlayerIndex)
{
	pLog.WriteLog("Coop::SpawnPlayer(%i)", (BYTE)PlayerIndex);
	/*if(Coop.Client_f==TRUE)
	{
	pLog.WriteLog("Coop:: Running Client Fixes.");
	Coop.Client_f==FALSE;
	CreateThread(0,0,( LPTHREAD_START_ROUTINE)ClientHooks,0,0,0);
	// ClientFixes();
	*(BYTE*)Coop.GameEngine = 1; //Engine Hack
	*(BYTE*)Coop.CoopSpawns = 1;//Lets Enable Coop Play
	}
	else if(Coop.Host_f==TRUE)
	{

	pLog.WriteLog("Coop:: Running Host Fixes.");
	Coop.Host_L=TRUE;
	Coop.Host_f=FALSE;
	}
	*/
	pSpawn(PlayerIndex);

}
signed int Test()
{
	typedef signed int(__cdecl * t)();
	t pt = (t)(((char*)game.GetBase()) + 0x51299);
	return pt();
}
void CoopAssignPointers()
{
	if (halo.H2Type == Halo2)
	{
		int GameGlobals = (int)*(int*)((char*)game.GetBase() + 0x482D3C);
		int GameTimeGlobals = (int)*(int*)((char*)game.GetBase() + 0x4C06E4);

		//pGameSet = (GameSet)(((char*)game.GetBase()) + 0x49E4C);
		pGameSet = (GameSet)(((char*)game.GetBase()) + 0x4A46E);

		//pCrashy001 = (Crashy)(((char*)game.GetBase())+ 0x1F2337);
		pFp = (Fp)(((char*)game.GetBase()) + 0x2295BE);
		pSpawn = (Spawn)(((char*)game.GetBase()) + 0x55952);
		Coop.Difficulty = GameGlobals + 0x2A2;
		Coop.GameType = GameGlobals + 0x2EC;
		Coop.CoopSpawns = GameGlobals + 0x2A4;
		Coop.GameEngine = GameGlobals + 0x8;
		Coop.PauseGame = GameTimeGlobals + 1;
		Coop.StausCheck = (int)((char*)game.GetBase() + 0x420FC4);
		Coop.PlayerCount = 0x30004B60;
		Coop.CoopTeam = 0;
		Coop.CoopBiped = 0;
	}
	else
	{
		int GameGlobals = (int)*(int*)((char*)game.GetBase() + 0x482D3C);
		int GameTimeGlobals = (int)*(int*)((char*)game.GetBase() + 0x4C06E4);


		pGameSet = (GameSet)(((char*)game.GetBase()) + 0x430CA);
		Coop.CoopTeam = 0;
		Coop.CoopBiped = 0;
	}

}
void MapThings()
{
	//0x47cf0c
	char* map_name = (char*)(((char*)game.GetBase()) + 0x47cf0c);
	if ((!strcmp(map_name, "01a_tutorial")) || (!strcmp(map_name, "01b_spacestation")) || (!strcmp(map_name, "03a_oldmombasa")) || (!strcmp(map_name, "03b_newmombasa")) || (!strcmp(map_name, "05a_deltaapproach")) || (!strcmp(map_name, "05b_deltatowers")) || (!strcmp(map_name, "07a_highcharity")) || (!strcmp(map_name, "07b_forerunnership")))
	{
		Coop.CoopBiped = 0;
		Coop.CoopTeam = 2;
	}
	else if ((!strcmp(map_name, "04a_gasgiant")) || (!strcmp(map_name, "04b_floodlab")) || (!strcmp(map_name, "06a_sentinelwalls")) || (!strcmp(map_name, "06b_floodzone")) || (!strcmp(map_name, "08a_deltacliffs")) || (!strcmp(map_name, "08b_deltacontrol")))
	{
		Coop.CoopBiped = 1;
		Coop.CoopTeam = 3;
	}
	pLog.WriteLog("Coop:: Current Coop Map : %s", map_name);

}
void CooperativeHook()
{

	CoopAssignPointers();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());


	DetourAttach(&(PVOID&)pGameSet, h_GameEngineSet);
	if (halo.H2Type == Halo2)
	{
		//DetourAttach(&(PVOID&)pSpawn, h_SpawnPlayer);
	}


	//DetourAttach(&(PVOID&)pSpawn, h3_SpawnPlayer);
	Coop.CoopGame = FALSE;
	DetourTransactionCommit();

	pLog.WriteLog("Hooks:: Cooperative Hooks Started.");
	pLog.WriteLog("Press F5 To Start Coop..");
	pLog.WriteLog("Press F4 For Bump Possession.");
	pLog.WriteLog("Coop:: Coop Status : %i", Coop.CoopGame);

	return;
}
void CooperativeUnHook()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	DetourDetach(&(PVOID&)pGameSet, h_GameEngineSet);
	DetourDetach(&(PVOID&)pFp, h_FpWeaponsSet);

	DetourTransactionCommit();
	pLog.WriteLog("Removed All Cooperative Hooks.");
	return;
}
void TempUnHook()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)pSpawn, h_SpawnPlayer);
	DetourDetach(&(PVOID&)pFp, h_FpWeaponsSet);
	DetourTransactionCommit();
	pLog.WriteLog("Removed Temporary Coop Hooks.");
	return;
}
void Fixes()
{


	*(BYTE*)Coop.CoopSpawns = 1;//Lets Enable Coop Play
	*(BYTE*)Coop.GameType = 0;


	//Lets Fix SomeThings
	for (int i = 0; i <16; i++)
	{
		*(int*)(0x30002BA0 + (i * 0x204)) = Coop.CoopBiped;
		*(int*)(0x30002BD8 + (i * 0x204)) = 1;//Default Team
	}


#pragma region Call_Functions
	/*Now Obselete Functions

	void(*AiActivate)();
	AiActivate =(void (*)(void))((char*)game.GetBase()+0x30E67C);
	AiActivate();

	signed int(*ObjScripting)();
	ObjScripting =(signed int (*)(void))((char*)game.GetBase()+0x14B083);
	ObjScripting();

	void(*ObjEarlyMovers)();
	ObjEarlyMovers =(void (*)(void))((char*)game.GetBase()+0x14B9D8);
	ObjEarlyMovers();

	int(*GameTime)();
	GameTime = (int(*)(void))((char*)game.GetBase() + 0x7C13D);
	GameTime();




	char(*PlayerGlobals)();
	PlayerGlobals = (char(*)(void))((char*)game.GetBase() + 0x52E03);
	PlayerGlobals();

	/*
	signed int(*GameEngineGlobals)();
	GameEngineGlobals =(signed int (*)(void))((char*)game.GetBase()+0x753B4);
	GameEngineGlobals();

	void(*Rasterizer)();
	Rasterizer =(void (*)(void))((char*)game.GetBase()+0x272986);
	Rasterizer();

	char(*GameSounds)();
	GameSounds =(char (*)(void))((char*)game.GetBase()+0x85801);
	GameSounds();

	char(*PlayerEffects)();
	PlayerEffects =(char (*)(void))((char*)game.GetBase()+0xA3E39);
	PlayerEffects();


	void(*UserScreen)();
	UserScreen =(void (*)(void))((char*)game.GetBase()+0x227862);
	UserScreen();

	char(*HsSystem)();
	HsSystem = (char(*)(void))((char*)game.GetBase() + 0x96BFD);
	HsSystem();




	char(*CinematicGlobals)();
	CinematicGlobals = (char(*)(void))((char*)game.GetBase() + 0x3A5F3);
	CinematicGlobals();

	void(*UserScreen)();
	UserScreen = (void(*)(void))((char*)game.GetBase() + 0x227862);
	UserScreen();

	int(*SaveState)();
	SaveState =(int (*)(void))((char*)game.GetBase()+0x9E455);
	SaveState();

	*/





#pragma region Notes
	//Functions in Sequence

	//GameTime
	//PlayerGlobals  
	//GameEngineGlobals
	//Rasterizer
	//GameSounds
	//PlayerEffects     //Causes Black Screen On SP Mode while Fade from black in MP
	//UserScreen
	//CinematicGlobals //Brings BlackLetterbox,Removes Sound..etc.
	//ObjPlacement
	//SaveState
#pragma endregion

#pragma region OldCrashyWay
	//I Stopped using this becuz it caused soo many non usefull functions to load like Game Shell BG
	//I better call them manually

	/*
	int off=0;
	void (*pInitzFunction)(void);

	//int *z=(int*)((char*)game.GetBase()+0x3A0470);
	int *dword_710470 =(int*)((char*)game.GetBase()+0x3A0470);
	//Now Calling all the GameInitialization Functions
	do
	{
	pInitzFunction = (void (*)(void))dword_710470[off];
	if ( pInitzFunction )
	pInitzFunction();
	off += 9;
	}
	while ( off < 0x276 );*/
#pragma endregion

#pragma endregion
}
void InitializeCoop()
{

	Coop.CoopGame = !Coop.CoopGame;
	pLog.WriteLog("Coop:: Coop Status : %i", Coop.CoopGame);

}

#pragma endregion