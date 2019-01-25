// dllmain.cpp : Defines the entry point for the DLL application.
#define PI 3.14159265
#define degreesToRadians(angleDegrees) (angleDegrees * PI / 180.0)
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / PI)

#include "stdafx.h"
#include "H2hooks.h"
#include "Cooperative.h"
#include"meta_loader\tag_loader.h"

H2class halo;
Debug Dbg;
Game game;

Logs pLog= Logs("H2Codez.log");

Cooperative Coop;

BOOL EnableDbgConsole;


//Enable Hooking System
void APPLYHOOKS()
{ 
  pLog.WriteLog("Hooks:: Initializing Hooking System....");   
  CreateThread(0, 0, (LPTHREAD_START_ROUTINE)H2Hooks, 0, 0, 0);
  //CreateThread(0,0,( LPTHREAD_START_ROUTINE)CooperativeHook,0,0,0);
  pLog.WriteLog("Hooks:: InProgress");

}
//Remove Hooking System
void DisEngageHOOKS()
{
    
DetourTransactionBegin();
CooperativeUnHook();
DetourTransactionCommit();
pLog.WriteLog("\n\n***H2 Codez ShutDown****");
pLog.Exit();

ExitProcess(true);
}

/*
char* SavedFilm = new char[0x12F8];
void PathGameTheatre()
{
	DWORD IngameMemorySaveCache = (DWORD)((char*)game.GetBase() + 0x47CD3C);
	memcpy(&SavedFilm[0x12F8 * 0], (void*)(*(DWORD*)IngameMemorySaveCache), 0x12F8);
	int c = (int)SavedFilm;
	BYTE *f = (BYTE*)(&c);
	BYTE Auxilary_Line[6] = { 0x81,0xC1,f[0],f[1],f[2],f[3] };//

	WriteBytesASM(game.GetBase() + 0x3062C, Auxilary_Line, 6);
	WriteBytesASM(game.GetBase() + 0x30010, Auxilary_Line, 6);

	pLog.WriteLog("SaveData Addr : %X", c);
	pLog.WriteLog("Reverse Addr : %X %X %X %X", f[0], f[1], f[2], f[3]);
}
*/


bool is_key_pressed(int VirtKey)
{
	return GetKeyState(VirtKey) < 0;
}
bool exiting = false;

DWORD WINAPI InputListner(LPVOID)
{

	while (!exiting)
	{

#if 0
		if (is_key_pressed(VK_F5))
		{
			/*ofstream os;
			os.open("C:\\FORGE\\new_locky.scnr",ios::binary);
			char* stream = my_forge_obj->Generate_Forge_Data("new_locky", "THIS IS A TEST LOL MAP :P :P :P");
			os.write(stream,sizeof(stream));
			os.close();
			*/

			//SwitchToCoop();
			//InitializeCoop();
			/*
			// SwitchToCoop();
			//int __cdecl sub_15E3305(char)
			//int __cdecl unit_exit_vehicle_2(int, int)
			if (isPicked)
			isPicked = FALSE;
			if (!isPicked)
			{
			ObjectSpawnData pSpawn;

			pSpawn.DatumIndex = 0xF28C3826;
			pSpawn.Position_X = *(float*)(((char*)game.GetBase()) + 0x4A8504);
			pSpawn.Position_Y = *(float*)(((char*)game.GetBase()) + 0x4A8508);
			pSpawn.Position_Z = (*(float*)(((char*)game.GetBase()) + 0x4A850C) + 1.8f);


			datum = halo.SpawnObj(pSpawn);


			if (datum != 0xFFFFFFFF)
			{
			my_sys.manipdatum = datum;
			isPicked = true;
			pLog.WriteLog("Got an Object");
			}
			else my_sys.manipdatum = 0xFFFFFFFF;
			}



			}
			ObjectSpawnData pSpawn;

			pSpawn.DatumIndex = Weapon::juggernaut_powerup;
			pSpawn.Position_X = *(float*)(((char*)game.GetBase()) + 0x4A8504);
			pSpawn.Position_Y = *(float*)(((char*)game.GetBase()) + 0x4A8508);
			pSpawn.Position_Z = (*(float*)(((char*)game.GetBase()) + 0x4A850C) + 1.8f);


			datum = halo.SpawnObj(pSpawn);
			int PlayerIndex = 0;
			*(int*)(0x30005960* PlayerIndex) = *(int*)(0x30005960*PlayerIndex) + 1;
			*/


		}




		if (is_key_pressed(VK_F10))
		{
			/*
			pLog.WriteLog("Coop::Fading from Black_White. ");
			*(BYTE*)Coop.GameEngine = 2;
			char(*PlayerEffects)();
			PlayerEffects = (char(*)(void))((char*)game.GetBase() + 0xA3E39);
			PlayerEffects();
			*(BYTE*)Coop.GameEngine = 1;
			*/

		}

		if (is_key_pressed(VK_NEXT))
		{
			//50A398
			//pLog.WriteLog("Party Privacy : InviteOnly ");
			//*(int*)((char*)game.GetBase() + 0x50A398) = 2;
		}

		if (is_key_pressed(VK_PRIOR))
		{
			//pLog.WriteLog("Party Privacy : Open ");
			//*(int*)((char*)game.GetBase() + 0x50A398) = 0;
		}

		if (is_key_pressed(VK_F6))
		{

			/*
			char* temp = new char[0x90];
			memcpy(temp, net_game_template, 0x90);

			my_forge_obj->Add_Forgeable_stuff(temp, 0);
			*/



			//SpawnAICharacters();


			/*
			DWORD IngameMemorySaveCache = (DWORD)((char*)game.GetBase() + 0x47CD3C);
			memcpy((void*)(*(DWORD*)IngameMemorySaveCache), &SavedFilm[0x12F8 * 0], 0x12F8u);

			pLog.WriteLog("Frame Loaded");
			*/
			//unsigned int targdatum = *(int*)0x30004D04;//ObjectDatum In CrossHair
			// *(int*)(GetPlayerDyanamic(0) + 0x1D4);

			//	if (datum != 0xFFFFFFFF)
			//		my_sys.manipdatum = datum;
			//	else my_sys.manipdatum = 0xFFFFFFFF;
			//RevertCP();


		}
#endif

		if (is_key_pressed(VK_F4))
		{
			//my_forge_obj->Add_stuff_to_Net_Game_List(0);

			/*if (*(int*)0x30004D04 != -1)
			{
			pLog.WriteLog("Bump Possessed!!");
			datum = *(int*)0x30004D04;//ObjectDatum In CrossHair
			game.call_AssignObjDatumToPlayer(0, datum);
			}
			pLog.WriteLog(":P Get A Target");
			*/

			//SpawnAICharacters();


			DWORD t = halo.SpawnObjAtCamera(0x3ba4);

			game.call_AssignObjDatumToPlayer(0, t);
			//game.call_AssignObjDatumToPlayer(0, halo.SpawnObjAtCamera(0x3BA4));

			/*
			DWORD IngameMemorySaveCache = (DWORD)((char*)game.GetBase() + 0x47CD3C);
			memcpy(&SavedFilm[0x12F8 * 0], (void*)(*(DWORD*)IngameMemorySaveCache), 0x12F8);
			DWORD byte_4DA72A = (DWORD)((char*)game.GetBase() + 0x47A72A);
			*(BYTE*)byte_4DA72A = 1;


			pLog.WriteLog("Frame Saved");

			pLog.WriteLog("%X", &SavedFilm);
			*/



		}
		Sleep(50);
	}
	return 0;
}

DWORD WINAPI Initialize(LPVOID)
{

	EnableDbgConsole = TRUE;
	halo.Start();
	APPLYHOOKS();

	Initialise_tag_loader();

	//DWORD cThread = 0x4A5B6;
	//PatchCall((DWORD)((char*)game.GetBase() + cThread), (DWORD)GameContinous);
	//PathGameTheatre();
	CreateThread(NULL, NULL, InputListner, NULL, NULL, NULL);
	return 0;
}





BOOL APIENTRY DllMain( HMODULE hModule,
	                   DWORD  ul_reason_for_call,
	                   LPVOID lpReserved
	                  )
{
	switch (ul_reason_for_call)
	{

	case DLL_PROCESS_ATTACH:
		Initialize(NULL);
        
	    break;
	
	case DLL_PROCESS_DETACH:
		exiting = true;
	    DisEngageHOOKS();
		break;
	}
	return TRUE;
}
