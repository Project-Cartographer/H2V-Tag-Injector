#include "stdafx.h"

#define PI 3.14159265
#define degreesToRadians(angleDegrees) (angleDegrees * PI / 180.0)
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / PI)



#pragma region H2Functions

#pragma region Halo

void H2class::Start()
{

	if (EnableDbgConsole)
		Dbg.Start_Console();
	pLog.WriteLog("\n*** H2 Codez***\nBETA v1.5\n :) \n");

	if (GetModuleHandleW(L"halo2.exe"))
	{
		game.g_base=GetModuleHandleW(L"halo2.exe");		
		this->H2Type = ProcessType::Halo2;
		pLog.WriteLog("Injected to : Halo 2");

	}
	else if (GetModuleHandleW(L"h2server.exe"))
	{

		game.g_base=GetModuleHandleW(L"h2server.exe");
		this->H2Type=ProcessType::H2Server;	
		pLog.WriteLog("Injected to : H2Server ");		

	}	
	

	pLog.WriteLog("Base Address : 0x%X",game.GetBase());
	

}



int H2class::get_unit_datum_from_player_index(int pIndex)
{
	int unit = 0;
	DWORD player_table_ptr = *(DWORD*)(game.GetBase() + 0x004A8260);
	player_table_ptr += 0x44;

	unit = (int)*(int*)(*(DWORD*)player_table_ptr + (pIndex * 0x204) + 0x28);

	return unit;
}


char __cdecl H2class::PlayerShieldExplosion(int Unit)
{
	typedef int(__cdecl * gg)(int);
	gg pallc = (gg)(((char*)game.GetBase()) + 0x17704C);
	return pallc(Unit);
}




int __stdcall H2class::MPMapSelect(int* a1)
{
	pLog.WriteLog("call_MP_MAPSELECT(%08X)", a1);
	typedef int(__stdcall *MapSelect)(int*);
	MapSelect pMapSelect = (MapSelect)(((char*)game.GetBase()) + 0x24F9A1);
	return pMapSelect(a1);
}
int __cdecl  H2class::call_ShowSettingsScreen(int a1)
{
	pLog.WriteLog("call_SettingsScreen(%08X)", a1);
	typedef int(__cdecl *sett)(int);
	sett psett = (sett)(((char*)game.GetBase()) + 0xB071);
	return psett(a1);
}



int __cdecl H2class::ShowSquadSettings(int* a1)
{
	pLog.WriteLog("call_ShowSquadSettings(%X(%X))", a1, *(int*)a1);
	typedef int(__cdecl * SquadSettings)(int*);
	SquadSettings psquadsettings = (SquadSettings)(((char*)game.GetBase()) + 0x24FE89);
	return psquadsettings(a1);
}

unsigned __int16 H2class::SpawnObj(ObjectSpawnData Data)
{
	pLog.WriteLog("Spanwing Object(Object_Datum Index : %X)", Data.DatumIndex);

	char* nObject = new char[0xC4];
	DWORD dwBack;

	VirtualProtect(nObject, 0xC4, PAGE_EXECUTE_READWRITE, &dwBack);
	game.call_object_placement_data_new(nObject, Data.DatumIndex, -1, 0);

	*((float*)nObject + 7) = Data.Position_X;
	*((float*)nObject + 8) = Data.Position_Y;
	*((float*)nObject + 9) = Data.Position_Z;	

	halo.ObjectSetOrientation((int)((float*)nObject + 10), (int)nObject + 0x34, &Data.Orientation_Yaw);

	*((float*)nObject + 0x10) = Data.Velocity_X;
	*((float*)nObject + 0x11) = Data.Velocity_Y;
	*((float*)nObject + 0x12) = Data.Velocity_Z;

	*((float*)nObject + 0x13) = Data.RotationSpeed_X;
	*((float*)nObject + 0x14) = Data.RotationSpeed_Y;
	*((float*)nObject + 0x15) = Data.RotationSpeed_Z;

	*((float*)nObject + 0x16) = Data.Scale;
		
	int mydatum = game.call_Object_create(nObject);
	game.call_ObjectSync(mydatum);
	delete[0xC4]nObject;
	return mydatum;


}
DWORD H2class::SpawnObjAtCamera(int datumindex)
{
	//pLog.WriteLog("SpanwingObject AtCamera(Object_Datum Index : %X)", datumindex);


	float* nObject = new float[0xC4];
	DWORD dwBack;

	VirtualProtect(nObject, 0xC4, PAGE_EXECUTE_READWRITE, &dwBack);
	game.call_object_placement_data_new(nObject, datumindex, -1, 0);

	nObject[7] = *(float*)(((char*)game.GetBase()) + 0x4A8504); //x
	nObject[8] = *(float*)(((char*)game.GetBase()) + 0x4A8508);//y
	nObject[9] = (*(float*)(((char*)game.GetBase()) + 0x4A850C) + 1.8f);//z
	

	int mydatum = game.call_Object_create(nObject);
	game.call_ObjectSync(mydatum);



	delete[0xC4]nObject;

	return mydatum;

}

int __cdecl H2class::ObjectSetOrientation(int ObjectYawAddress, int ObjScaleadd, void* DataYawAddr)
{
	typedef int(__cdecl *ObjectSetOrientation)(void*, void*, void*);
	ObjectSetOrientation pcamotounit = (ObjectSetOrientation)(((char*)game.GetBase()) + 0x3347B);
	return pcamotounit((void*)ObjectYawAddress, (void*)ObjScaleadd, DataYawAddr);

}


int __cdecl H2class::unit_set_active_camo(int Unit, char Active, float Strength)
{


	pLog.WriteLog("unit_set_active_camo(%08X,%i,%04f)", Unit, Active, Strength);

	typedef int(__cdecl *camotounit)(int, char, float);
	camotounit pcamotounit = camotounit(((char*)game.GetBase()) + 0x184555);
	return pcamotounit(Unit, Active, Strength);


}



void H2class::GivePlayerWeapon(int PlayerIndex, int WeaponId)
{
	pLog.WriteLog("GivePlayerWeapon(PlayerIndex :%d ,WeaponID : %X)", PlayerIndex, WeaponId);


	int unit_datum = halo.get_unit_datum_from_player_index(PlayerIndex);


	if (unit_datum != -1 && unit_datum != 0)
	{
		char* nObject = new char[0xC4];
		DWORD dwBack;
		VirtualProtect(nObject, 0xC4, PAGE_EXECUTE_READWRITE, &dwBack);

		game.call_object_placement_data_new(nObject, WeaponId, unit_datum, 0);

		int object_index = game.call_Object_create(nObject);
		pLog.WriteLog("Object Index : %X", object_index);

		game.call_unit_reset_equipment(unit_datum);

		game.call_assign_equipment_to_unit(unit_datum, object_index, 1);
	}



}
void H2class::CameraMod(int Type)
{
	int cam=(int)((char*)game.GetBase()+0x4a84b0);
	int height=(int)((char*)game.GetBase()+0x4A84CC);
	switch(Type)
	{
	case 1:
		*(int*)cam=0x001FD7E1;//FP
		*(float*)height=0.0f;
		break;
	case 2:
		*(int*)cam=0x001C8039;//Static
		break;
	case 3:
		*(int*)cam=0x001FD144;//TP
		*(float*)height=1.0f;
		break;
	default:
		*(int*)cam=0x001FD7E1;
		

	}
	
}

char __cdecl H2class::SetBipedStateRelated(int UnitDatum)
{
	typedef char(__cdecl *get_object)(int);
	get_object pget_object = (get_object)(((char*)game.GetBase()) + 0x157078);
	return pget_object(UnitDatum);
}
char __thiscall H2class::SetBipedState(int PlayerStateAddr, char PlayerState)
{
	typedef char(__thiscall *get_object)(int,char);
	get_object pget_object = (get_object)(((char*)game.GetBase()) + 0xC854D);
	return pget_object(PlayerStateAddr,PlayerState);
}

#pragma endregion

#pragma region Game

DWORD Game::GetBase()
{	
	return (DWORD)(this->g_base);	
}


int __cdecl Game::call_get_object(signed int object_datum_index, int object_type)
{
	//pLog.WriteLog("call_get_object(object_datum_index : %08X , object_type : %i)", object_datum_index,object_type);

	typedef int(__cdecl *get_object)(signed int , int );
	get_object pget_object = (get_object)(((char*)game.GetBase())+ 0x1304E3);
	return pget_object(object_datum_index, object_type);
}


int __cdecl Game:: call_unit_reset_equipment(int unit_datum_index)
{
	typedef int(__cdecl *unit_reset_equipment)(int unit_datum_index);
	unit_reset_equipment punit_reset_equipment = (unit_reset_equipment)(((char*)game.GetBase()) + 0x1441E0);

	if (unit_datum_index != -1 && unit_datum_index != 0)
	{
		return punit_reset_equipment(unit_datum_index);
	}

	return 0;
}

int __cdecl Game:: call_hs_object_destroy(int object_datum_index)
{

	typedef int(__cdecl *hs_object_destroy)(int object_datum_index);
	hs_object_destroy phs_object_destroy = (hs_object_destroy)(((char*)game.GetBase()) + 0x136005);

	return phs_object_destroy(object_datum_index);
}

signed int __cdecl Game:: call_unit_inventory_next_weapon(unsigned short unit)
{

	typedef signed int(__cdecl *unit_inventory_next_weapon)(unsigned short unit);
	unit_inventory_next_weapon punit_inventory_next_weapon = (unit_inventory_next_weapon)(((char*)game.GetBase()) + 0x139E04);

	return punit_inventory_next_weapon(unit);
}

bool __cdecl Game:: call_assign_equipment_to_unit(int unit, int object_index, short unk)
{

	typedef bool(__cdecl *assign_equipment_to_unit)(int unit, int object_index, short unk);
	assign_equipment_to_unit passign_equipment_to_unit = (assign_equipment_to_unit)(((char*)game.GetBase()) + 0x1442AA);

	return passign_equipment_to_unit(unit, object_index, unk);
}




signed int __cdecl Game:: call_Object_create(void * objplacementdata)
{

	//pLog.WriteLog("call_Object_create(0x%08X)", objplacementdata);
	typedef signed int (__cdecl *Functionaddr)(void*); 
	Functionaddr pObject_create = (Functionaddr)(((char*)game.GetBase())+0x136CA7);
	return pObject_create(objplacementdata);
	
}

int __cdecl Game:: call_object_placement_data_new(void* s_object_placement_data, int object_definition_index, int object_owner, int unk)
{
	//pLog.WriteLog("call_object_placement_data_new(%08X, %08X, %08X , %08X)", s_object_placement_data,object_definition_index,object_owner,unk);
	typedef int(__cdecl *object_placement_data_new)(void*, int, int, int);
	object_placement_data_new pobject_placement_data_new = (object_placement_data_new)(((char*)game.GetBase()) + 0x132163);
	return pobject_placement_data_new(s_object_placement_data, object_definition_index, object_owner, unk);
}

	
	int __cdecl Game::Allocator(int size)
    {
       // pLog.WriteLog("call_Allocator(%X)", size);
        typedef int(__cdecl * allc)(int);
        allc pallc = (allc)(((char*)game.GetBase()) + 0x20D2D8);
        return pallc(size);
    }
	char __cdecl Game::call_ObjectSync(int GameObjectDatum)
	{

		typedef char(_cdecl *Sync)(int);
		Sync psync =(Sync)(((char*)game.GetBase()) + 0x1B8D14);
		return psync(GameObjectDatum);

	}

	void*__cdecl Game::call_CreateCharacter(int CharDatumIndex, signed __int16 squad_index, void* a3)
	{
		pLog.WriteLog("CreateCharacter(%X,%X,%X)", CharDatumIndex, squad_index, a3);
		typedef void*(__cdecl *createchar)(int, signed __int16 , void* );
		createchar pcreatechar = (createchar)(((char*)game.GetBase()) + 0x318B0E);
		return pcreatechar(CharDatumIndex, squad_index, a3);
	}
	void __cdecl Game::call_CharacterInitialize(void *SpawnData)
	{
		
		typedef void(__cdecl *initializechar)(void*);
		initializechar pinitializechar = (initializechar)(((char*)game.GetBase()) + 0x33FBDC);
		pinitializechar(SpawnData);
	}
	
	int _cdecl Game::call_AssignObjDatumToPlayer(int pIndex, int UnitDatum)
	{
		typedef int(__cdecl * assign)(int,int);
		assign passign = (assign)(((char*)game.GetBase()) + 0x556BE);
		return passign(pIndex,UnitDatum);

	}
	int Game::object_set_position(int unit_datum, float* position,float* orientation)
	{
		int(__cdecl* object_set_position)(int , float*, float*, float*, float*);
		object_set_position = (int(__cdecl*)(int, float*, float*, float*, float*))((char*)game.GetBase() + 0x136b7f);
		return object_set_position(unit_datum, position, orientation, 0, 0);
	}
	char __cdecl Game::object_set_velocity_(int datum, float X_velocity, float Y_velocity, float Z_velocity)
	{
		char(__cdecl* object_set_position)(int, float, float, float);
		object_set_position = (char(__cdecl*)(int, float, float, float))((char*)game.GetBase() + 0x14B83F);
		return object_set_position(datum, X_velocity, Y_velocity, Z_velocity);
	}
	

#pragma endregion


#pragma endregion