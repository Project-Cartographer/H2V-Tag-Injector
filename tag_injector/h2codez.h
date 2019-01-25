#include "stdafx.h"


enum ProcessType
{
	H2Game,
	H2Server,
	Invalid
};

struct ObjectSpawnData
{
	unsigned int DatumIndex;   //ObjectDefination Index 
	float Position_X = 0;          //Map X Co-ordinate
	float Position_Y = 0;          //Map Y Co-ordiante
	float Position_Z = 0;          //Map Z Co-ordiante

	float Orientation_Yaw = 0;     //Rotation in Axis Yaw(Radians)
	float Orientation_Pitch = 0;   //Rotation in Axis Pitch(Radians)
	float Orientation_Roll = 0;    //Rotation in Axis Roll(Radians)

	float Velocity_X = 0;          //Velocity of Object in X Axis
	float Velocity_Y = 0;          //Velocity of Object in Y Axis
	float Velocity_Z = 0;          //Velocity of Object in Z Axis

	float RotationSpeed_X = 0;     //RotationSpeed of Object in X Axis
	float RotationSpeed_Y = 0;     //RotationSpeed of Object in Y Axis
	float RotationSpeed_Z = 0;     //RotationSpeed of Object in Z Axis

	float Scale = 1;               //Scale of Object
};

class H2class
{
public:

	 ProcessType H2Type;	 //Process is Halo 2 or H2Server	
	 
							 //Initialize Things
	 void Start();
	 //Gets Player Unit Datum from Player Index
	 int get_unit_datum_from_player_index(int pIndex); 

     char __cdecl PlayerShieldExplosion(int Unit);
	

	 


	 int __stdcall MPMapSelect(int* a1);
	 int __cdecl call_ShowSettingsScreen(int a1);
	 
	 int __cdecl ObjectSetOrientation(int ObjectYawAddress, int ObjScaleadd, void* DataYawAddr);
	 int __cdecl ShowSquadSettings(int* a1);
	 unsigned __int16 SpawnObj(ObjectSpawnData DataPointer);
	 DWORD SpawnObjAtCamera(int datumindex);




	 void GivePlayerWeapon(int PlayerIndex, int WeaponId);
	 int __cdecl unit_set_active_camo(int Unit, char Active, float Time);

	void CameraMod(int Type);
	char __cdecl SetBipedStateRelated(int UnitDatum);
	char __thiscall SetBipedState(int PlayerStateAddr, char PlayerState);

	 


};

class Game
{
public:
	//Holds the Process Base
	 HMODULE g_base;

	 //Returns The Base Address
	 DWORD GetBase();

	int __cdecl call_get_object(signed int object_datum_index, int object_type);
	//Reset Units Equipment
	int __cdecl call_unit_reset_equipment(int unit_datum_index);
	//Destroy Object
	int __cdecl call_hs_object_destroy(int object_datum_index);
	signed int __cdecl call_unit_inventory_next_weapon(unsigned short unit);
	//Assigns an Equipment to the Unit
	bool __cdecl call_assign_equipment_to_unit(int unit, int object_index, short unk);
	//Initializes SpawnData of the Object
	int __cdecl call_object_placement_data_new(void* s_object_placement_data, int object_definition_index, int object_owner, int unk);
	//Spawns an object Based on its SpawnData
	signed int __cdecl call_Object_create(void * objplacementdata);
	//SyncObject
	char __cdecl call_ObjectSync(int GameObjectDatum);

	void* __cdecl call_CreateCharacter(int CharDatumIndex, signed __int16 WepIndex, void* SpawnData);

	void __cdecl call_CharacterInitialize(void *SpawnData);
	int __cdecl call_AssignObjDatumToPlayer(int pIndex, int UnitDatum);
	int object_set_position(int , float* , float*);
	char __cdecl object_set_velocity_(int datum, float , float , float);
	
	


   // char __stdcall ObjInitializeData(int* datum_index_pointer, void* obj_network_data, int unk, void* nObject);
   // void __stdcall ObjCreation(int* datum_index_pointer, void* obj_network_data, int unk, void* nObject);


    int __cdecl Allocator(int size);



};







extern Game game;

extern H2class halo;