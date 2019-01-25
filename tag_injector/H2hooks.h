#include "stdafx.h"
#include "Patches.h"
#include "Forge.h"


#pragma once

using namespace std;
int *TEST,*b,c;
int *SS,k,*p;
int* myThis;


int *mya3;


Forge* my_forge_obj = nullptr;//my forge object
char* net_game_template = nullptr;//template of the net game stuff

/*
struct extra_tags_info
{
	//int datum_index;
	//int type;
	int mem_addr;
	int size;
	int mapIndex;
};
extra_tags_info* Etag_info;
*/

//CRAP
extern BOOL isPicked;
extern unsigned int datum;



#pragma  region H2Hooks

#pragma  region Declarations
//Declarations


//char *__cdecl sub_EDFF1D(int a1, int a2, unsigned int a3)
typedef char *(__cdecl *sub_EDFF1D)(int,int,unsigned int);
sub_EDFF1D psub_EDFF1D;

//void __thiscall GetGameOptions(int this, int a2, int *a3)
typedef void(__thiscall* GameOptions)(void*,int,int);
GameOptions pgameoptions;

//int __stdcall call_MPMapSelect(int a1)
typedef int(__stdcall* MapSelect)(int);
MapSelect pMapSelect;

typedef int(__stdcall* MpGame)(int);
MpGame pMpgame;

typedef void(_stdcall* XX)(int);
XX pxx;

//int __cdecl call_SquadSettingsDialog(int a1)
typedef int(__cdecl* SquadSettings)(int);
SquadSettings psquadsettings;

//int __usercall sub_12EAABD@<eax>(double a1@<st0>)
typedef int(_cdecl* PlayerSpeed)(double);
PlayerSpeed pPlayerSpeed;

typedef char(__cdecl *attach)(unsigned __int16, int);
attach pattach;

//int __cdecl CreateCharacter(int CharDatumIndex, signed __int16 a2, int a3)

typedef int(__cdecl *createchar)(int , signed __int16, int* );
createchar pcreatechar;

//char __stdcall sub_154CF0B(int a1, int a2, int pXml);

typedef char(__stdcall *sub_154CF0B)(int, int, int);
sub_154CF0B psub_154CF0B;

//int __cdecl GetSpawnData(int ObjectPtr, int flagsPtr, int entrysize);

//typedef int(__cdecl *SpawnData)(void*, void*, int);
//SpawnData pSpawnData;

//************MYCODE******************

void H2Hooks();
int __cdecl GetSpawnData_org(void* ObjectPtr, void* flagsPtr, int entrysize);


void arrayCpy(BYTE *src,BYTE *dest,int size)
{
	for (int i = 0;i < size;i++)
		*dest++ = *src++;

}
int MyContainerIndex = 0;//My Container
//char* SavedFilm = new char[0x12F8];




void TheatreDump()
{
	void(_cdecl*sub_EC21B)(int);
	sub_EC21B = (void(_cdecl*)(int))((char*)game.GetBase() + 0x8C21B);	
	void(_cdecl*sub_EC23F)(int);
	sub_EC23F = (void(_cdecl*)(int))((char*)game.GetBase() + 0x8C23F);

	DWORD word_4DCD24 = (DWORD)((char*)game.GetBase() + 0x47CD24);
	int dword_4DCD20 = (int)((char*)game.GetBase() + 0x47CD20); //=*(float*)300029C8+8;
	DWORD byte_4DA72B = (DWORD)((char*)game.GetBase() + 0x47A72B);
	DWORD byte_4DA72A = (DWORD)((char*)game.GetBase() + 0x47A72A);

	DWORD IngameMemorySaveCache = (DWORD)((char*)game.GetBase() + 0x47CD3C);


	//sub_EC21B(0);
	//*(WORD*)word_4DCD24 = 0;
	//*(float*)dword_4DCD20 = *(float*)(0x300029C8 + 8);
	//*(BYTE*)byte_4DA72B = *(BYTE*)byte_4DA72A;

	//byte_4DA72A = 1;	
    //memcpy(&SavedFilm[0x12F8 * 0], (void*)(*(DWORD*)IngameMemorySaveCache), 0x12F8u);
	//sub_EC23F(0);
	MyContainerIndex++;

}

#pragma  endregion 
#pragma region HookedFunctions

int GameContinous()
{
	//This is  a GameTimeGlobals Update function which Executes 24x7 (Will work here like a thread)
	int(*Loop)(void);
	Loop = (int(*)(void))((char*)game.GetBase() +0x7BFF2);
	int a = Loop();

	/*
	if (my_forge_obj != nullptr)
	{
		my_forge_obj->Update_Forge();
	}


	//We arent gonna use the following crap
	if (isPicked)
	{
		if (my_sys.manipdatum != 0xFFFFFFFF)
		{
			my_sys.cam_x = *(float*)(game.GetBase() + 0x4A8504);
			my_sys.cam_y = *(float*)(game.GetBase() + 0x4A8508);
			my_sys.cam_z = *(float*)(game.GetBase() + 0x4A850C);

			my_sys.alpha = *(float*)(game.GetBase() + 0x4A852C);
			my_sys.beta = *(float*)(game.GetBase() + 0x4A8530);
			my_sys.gamma = *(float*)(game.GetBase() + 0x4A8534);

			my_sys.obj_X = my_sys.range*my_sys.alpha;
			my_sys.obj_Y = my_sys.range*my_sys.beta;
			my_sys.obj_Z = my_sys.range*my_sys.gamma;

			my_sys.obj_x = my_sys.cam_x + my_sys.obj_X;
			my_sys.obj_y = my_sys.cam_y + my_sys.obj_Y;
			my_sys.obj_z = my_sys.cam_z + my_sys.obj_Z;

			float* loc = new float[3];
			*((float*)loc) = my_sys.obj_x;
			*((float*)loc + 1) = my_sys.obj_y;
			*((float*)loc + 2) = my_sys.obj_z;
		
			///pLog.WriteLog("Updating XYZ");
			game.object_set_position(my_sys.manipdatum, &my_sys.obj_x);
		}
	}
	if(MyContainerIndex>0&& MyContainerIndex<=10)
		pLog.WriteLog("Dumping SAveState Started XYZ");
	TheatreDump();

	*/
	return a;
}

void Func01new()
{
	bool(*FuncP)();
	FuncP = (bool(*)(void))((char*)game.GetBase() + 0x1AD940);
	bool(_stdcall *FuncQ)(int);
	FuncQ = (bool(_stdcall*)(int))((char*)game.GetBase() + 0x216901);

	*(DWORD*)((char*)game.GetBase() + 0x973A7C) = 0xFFFFFFFF;
	*(DWORD*)((char*)game.GetBase() + 0x973A80) = 0xFFFFFFFF;
	*(DWORD*)((char*)game.GetBase() + 0x973A84) = 0xFFFFFFFF;
	*(int*)((char*)game.GetBase() + 0x973A88) = 0;
	*(char*)((char*)game.GetBase() + 0x973A78) = 0;
	if (FuncP())
		FuncQ(0);
}
void SwitchToCoop()
{
	bool(*Func01)();
	Func01 = (bool(*)(void))((char*)game.GetBase() + 0x2171A0);
	char(_cdecl*Func02)(int);
	Func02 = (char(_cdecl*)(int))((char*)game.GetBase() + 0x217138);
	signed int(__cdecl*Coop_02)(void*);
	Coop_02 = (signed int(__cdecl*)(void*))((char*)game.GetBase() + 0x3223E);
	signed int(__cdecl*Coop_00)(int);
	Coop_00 = (signed int(__cdecl*)(int))((char*)game.GetBase() + 0x209E44);
	int byte_54E7CC = (int)((char*)game.GetBase() + 0x973A8C);
	bool(__cdecl*Coop_01Diffi)(int);
	Coop_01Diffi = (bool(__cdecl*)(int))((char*)game.GetBase() + 0x215624);
	int(__thiscall*sub_1331BA1)(void*);
	sub_1331BA1 = (int(__thiscall*)(void*))((char*)game.GetBase() + 0x211BA1);
	int(__thiscall*Func03)(int, int);
	Func03 = (int(__thiscall*)(int, int))((char*)game.GetBase() + 0x212604);

	//Now Calling Switch To Coop
	char(_cdecl*PregameLobby)(char,char);
	PregameLobby = (char(_cdecl*)(char,char))((char*)game.GetBase() + 0x216345);



	pLog.WriteLog("Starting Call Sequence");
	PregameLobby(1, 1);
	Func01new();		// sub_199A57
	Func02(0);	//LoadLobbyThings
/*
int v6;
	if (myThis != 0)
	{
		pLog.WriteLog("Starting Call Sequence");
		Func01();		// sub_199A57
		Func02(0);	//LoadLobbyThings
		Coop_02(&v6); //Coop_02//get_game_difficulty
		__int16 v3 = Coop_00(v6); //Coop_00
		*(BYTE*)byte_54E7CC = 0;//byte_54E7CC
		Coop_01Diffi(v3);  //DifficultyRelated
		int v5 = sub_1331BA1(myThis); //sub_22EEEE
		Func03(v5, 3); //call_REsume
	}
	*/

}
void SwitchToCustomGame()
{
	bool(*Func01)();
	Func01 = (bool(*)(void))((char*)game.GetBase() + 0x2171A0);
	char(_cdecl*Func02)(int);
	Func02 = (char(_cdecl*)(int))((char*)game.GetBase() + 0x217138);
	signed int(__cdecl*Coop_02)(void*);
	Coop_02 = (signed int(__cdecl*)(void*))((char*)game.GetBase() + 0x3223E);
	signed int(__cdecl*Coop_00)(int);
	Coop_00 = (signed int(__cdecl*)(int))((char*)game.GetBase() + 0x209E44);
	int byte_54E7CC = (int)((char*)game.GetBase() + 0x973A8C);
	bool(__cdecl*Coop_01Diffi)(int);
	Coop_01Diffi = (bool(__cdecl*)(int))((char*)game.GetBase() + 0x215624);
	int(__thiscall*sub_1331BA1)(void*);
	sub_1331BA1 = (int(__thiscall*)(void*))((char*)game.GetBase() + 0x211BA1);
	int(__thiscall*Func03)(int, int);
	Func03 = (int(__thiscall*)(int, int))((char*)game.GetBase() + 0x212604);
	signed int(__cdecl*CG)();
	CG = (signed int(__cdecl*)(void))((char*)game.GetBase() + 0x2169C5);

	pLog.WriteLog("Starting Call Sequence");
	Func01();		// sub_199A57
	Func02(2);	//LoadLobbyThings
	CG();        //sub_19A864
	int v5 = sub_1331BA1(myThis); //sub_22EEEE
	Func03(v5, 3); //call_REsume
	
}
void __fastcall h_GetGameOptions(void* This, void* garbage,  int a2,int a3)
{
 
    pLog.WriteLog("Hooks:: GetGameOptions(%08X,%08X,%08X)",(int*)This,a2,a3);   
    myThis=(int*)This;
    int i =*(int*)a3;
    int j = (*(DWORD *)(*((DWORD *)This + 0x1C) + 0x44) + 4 * (unsigned __int16)i + 2);
    pLog.WriteLog("Hooks:: GetGameOptions(%X(%i)",j,(WORD*)j); 
	pLog.WriteLog("Executing SwitchToCustomGame()");
	//SwitchToCoop();    //Crashes..
	SwitchToCustomGame(); //Works <3
    return pgameoptions(This,a2,a3);

}



int __stdcall h_MPMapSelect(int a1)
{
   pLog.WriteLog("Hooks:: MPMAPSELECT(%X(%X))",a1,*(int*)a1); 
    TEST=(int*)(a1);
    b=&c;
    c=*((int*)(*TEST));
    TEST=(int*)&b;
   
    return pMapSelect(a1); // pMapSelect(a1);
}


int __cdecl h_SquadSettings(int a1)
{
     pLog.WriteLog("Hooks:: SquadSettings(%X(%X))",a1,*(int*)a1);

     
	 SS = (int*)a1;
     k=*((int*)(*SS));
     p=&k;
     SS=(int*)&p;
     

     return psquadsettings(a1);
}



#pragma endregion

void RevertCP()
{
	//void __cdecl DumpSaveDataToGameState(unsigned int arg0)
	void(_cdecl* DumpSaveDataToGameState)(unsigned int);
	DumpSaveDataToGameState = (void(_cdecl*)(unsigned int))((char*)game.GetBase() + 0x305DA);
	DumpSaveDataToGameState(0x0);
}

/*
int __cdecl GetSpawnData_org(void* ObjectPtr, void* flagsPtr, int entrysize)
{
	return pSpawnData(ObjectPtr, flagsPtr, entrysize);
}
*/


//Set Addresses of Function  Pointers
void H2AssignPointers()
{
   
    psub_EDFF1D =(sub_EDFF1D)(((char*)game.GetBase())+ 0x2FF1D);

    pgameoptions =(GameOptions)(((char*)game.GetBase())+ 0x24FA19);
    pMapSelect =(MapSelect)(((char*)game.GetBase())+ 0x24F9A1);
    pMpgame =(MpGame)(((char*)game.GetBase())+ 0x24F9DD);
    pxx=(XX)(((char*)game.GetBase())+ 0x24F5FD);
    psquadsettings=(SquadSettings)(((char*)game.GetBase())+ 0x24FE89);
    pPlayerSpeed=(PlayerSpeed)(((char*)game.GetBase())+ 0x6AABD);

	pcreatechar=(createchar)(((char*)game.GetBase()) + 0x318B0E);

	psub_154CF0B =(sub_154CF0B)(((char*)game.GetBase()) + 0x1FCF0B);

	 // pattach = (attach)(((char*)game.GetBase()) + 0x13A2A6);


}

//Enable H2Function Hooks
void H2Hooks()
{
    H2AssignPointers();




#pragma  region Attach  Functions


	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

    //DetourAttach(&(PVOID&)PointerAddr,HookFunction);


	//DetourAttach(&(PVOID&)pgetobj,Hook01);
	//DetourAttach(&(PVOID&)pupdate,Hook02);
	//DetourAttach(&(PVOID&)pupdate2,Hook03);
	//DetourAttach(&(PVOID&)pobjnew,Hook04);

	//DetourAttach(&(PVOID&)punit,CreateUnit);
	//DetourAttach(&(PVOID&)pvehi,CreateVehi);
	//DetourAttach(&(PVOID&)pitem,CreateItem);
	//DetourAttach(&(PVOID&)pwep,CreateWep);
   // DetourAttach(&(PVOID&)psub_EDFF1D,h_sub_EDFF1D);
   // DetourAttach(&(PVOID&)pgameoptions,h_GetGameOptions);	
  // DetourAttach(&(PVOID&)pMapSelect,h_MPMapSelect);	
   //DetourAttach(&(PVOID&)psquadsettings,h_SquadSettings);	
   //  DetourAttach(&(PVOID&)pPlayerSpeed,OnPlayerSpeed);	

 //  DetourAttach(&(PVOID&)pcreatechar,h_CreateCharacter);
	//DetourAttach(&(PVOID&)pXYZ, h_XYZUpdate);
   
   

    DetourTransactionCommit();	

#pragma endregion
    pLog.WriteLog("Hooks:: H2Functions Hooked.");
	return;

}

//Remove Halo 2 Hooks
VOID H2Unhook()
{
     //DetourDetach(&(PVOID&)FunctionPointerAddress,HookFunction);
	pLog.WriteLog("Hooks:: Releasing H2Hooks.");

  


   //DetourDetach(&(PVOID&)pgameoptions,h_GetGameOptions);
   // DetourDetach(&(PVOID&)pMapSelect,h_MPMapSelect);
   // DetourDetach(&(PVOID&)psquadsettings,h_SquadSettings);	
	return;
}


#pragma endregion