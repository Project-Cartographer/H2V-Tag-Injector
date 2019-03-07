#include "stdafx.h"
#include "Forge.h"

//parameter to denote whether custom tags are loaded and forge_maps are loaded
Forge::Forge(bool custom_tags,bool forge_maps)
{
	//Initialise some stuff
	MapMemBase = *(DWORD*)(game.GetBase() + 0x47CD64);
	TagTableStart = *(DWORD*)(game.GetBase() + 0x47CD50);

	//null some stuff
	for (int i = 0;i < MAX_PLAYERS; i++)
	{
		range[i] = 5;
		net_game_manip_data[i] = nullptr;
	}

	//rip some stuff
	RIP_scnr();

	//patch some stuff
	PatchCall((DWORD)((char*)game.GetBase() + CTHREAD), (DWORD)GameContinous);

	pLog.WriteLog("Forge Initialised");
}
//a Destructor fix some stuff
Forge::~Forge()
{
	//unpatch stuff
	PatchCall((DWORD)((char*)game.GetBase() + CTHREAD), (DWORD)((char*)game.GetBase() + 0x7BFF2));
}
//Does all the shredding of the scnr
void Forge::RIP_scnr()
{
	scnr_memaddr = *(DWORD*)(TagTableStart + (0x0 * 0x10) + 0x8);//scnr index is 0x0 in most cases

	/********************* NET GAME STUFF *********************************/

	net_game_equip_array = new char[MAX_NETGAME_EQUIPMENTS*0x90];//declaring our new list(and size of a netgame field is 0x90)

	net_game_equip_count = (int*)(MapMemBase + scnr_memaddr + 0x120);//pointing to the count of net_game equipments()
	DWORD mem_addr= *(DWORD*)(MapMemBase + scnr_memaddr + 0x124);//the next 4 bytes give the mem_addr of the respective field

	memcpy(net_game_equip_array, (void*)(MapMemBase + mem_addr), *net_game_equip_count * 0x90);//time to copy that stuff

	*(DWORD*)(MapMemBase + scnr_memaddr + 0x124) = (DWORD)net_game_equip_array - MapMemBase;//time to point to our stuff
}
//Adding stuff to the net_game_equipment list and frees the linked net_game_manip_data
void Forge::Add_stuff_to_Net_Game_List(BYTE player_index)
{
	Net_Game_Equipment* stuff = net_game_manip_data[player_index];

	stuff->Sync_data_and_equip();

	memcpy(net_game_equip_array + *net_game_equip_count * 0x90, stuff->data, 0x90);//field stuff
	
	//net game table stuff
	//*(DWORD*)(NET_GAME_TABLE_START + 0x8 * (*net_game_equip_count)) = net_game_manip[player_index];
	*(DWORD*)(NET_GAME_TABLE_START + 0x8 * (*net_game_equip_count) + 0x4) = 0x1;//to respawn,

	//linking the dynamic object with its netgame table
	*(DWORD*)(GetObjectDynamic(stuff->ingamedatum) + 0xAF) = (DWORD)*net_game_equip_count;

	//updating the count
	*net_game_equip_count = *net_game_equip_count + 1;

	DWORD temp = stuff->ingamedatum;

	//now some cleaning stuff
	net_game_manip_data[player_index] = nullptr;
	delete stuff;	

	//for some unknown cause i have to delete the object,so that it is created by the net game loop
	game.call_hs_object_destroy(temp);
}
//Adds a Forgable stuff and links it to the concerned player for manipulation
void Forge::Add_Forgeable_stuff(char *data, BYTE player_index)
{
	//before adding control to a new object we will be removing controls from the previously manipulated object(if so)
	if (net_game_manip_data[player_index] != nullptr)
	{
		if (net_game_manip_data[player_index]->ingamedatum != -1)
		{
			Add_stuff_to_Net_Game_List(player_index);
		}
	}
	//Lets create our stuff
	Net_Game_Equipment *stuff = new Net_Game_Equipment(data);
	DWORD objdatum = halo.SpawnObjAtCamera(stuff->Get_datum_index());
	stuff->ingamedatum = objdatum;

	//and dont forget to store a pointer to the net_game_data
	net_game_manip_data[player_index] = stuff;
}
//Carries out all the update task
void Forge::Update_Forge()
{
	//Manipulate object
	for (int i = 0;i < MAX_PLAYERS;i++)
	{
		if (net_game_manip_data[i] != nullptr)
		{
			if (net_game_manip_data[i]->ingamedatum != -1)
			{
				cartessian_co_ord my_sys;

				float initial_x, initial_y, initial_z;
				float final_x, final_y, final_z;
				float disp_x, disp_y, disp_z;

				int Object_DA = GetObjectDynamic(net_game_manip_data[i]->ingamedatum);

				//If our Object is a Scenary Type(whose velocity cannot be altered) ,we teleport it 
				if (*(BYTE*)(Object_DA + 0xAA) == 6)
					this->teleport_object_to_player_cam(i);
				else
				{
					initial_x = *(float*)(Object_DA + 0x64);
					initial_y = *(float*)(Object_DA + 0x68);
					initial_z = *(float*)(Object_DA + 0x6C);

					//**** FIX these stuff so that they refer to each player individualy
					my_sys.cam_x = *(float*)(game.GetBase() + 0x4A8504);
					my_sys.cam_y = *(float*)(game.GetBase() + 0x4A8508);
					my_sys.cam_z = *(float*)(game.GetBase() + 0x4A850C);

					my_sys.alpha = *(float*)(game.GetBase() + 0x4A852C);
					my_sys.beta = *(float*)(game.GetBase() + 0x4A8530);
					my_sys.gamma = *(float*)(game.GetBase() + 0x4A8534);

					my_sys.i_obj_X = range[i] * my_sys.alpha;
					my_sys.i_obj_Y = range[i] * my_sys.beta;
					my_sys.i_obj_Z = range[i] * my_sys.gamma;

					//Where our object should be
					final_x = my_sys.cam_x + my_sys.i_obj_X;
					final_y = my_sys.cam_y + my_sys.i_obj_Y;
					final_z = my_sys.cam_z + my_sys.i_obj_Z;

					//calculating Displacement
					disp_x = (final_x - initial_x);
					disp_y = (final_y - initial_y);
					disp_z = (final_z - initial_z);

					//Multiplying Displacement by Velocity Const And Adding Velocity
					game.object_set_velocity_(net_game_manip_data[i]->ingamedatum, disp_x * VELOCITY_CONST, disp_y * VELOCITY_CONST, disp_z * VELOCITY_CONST);

				}
			}
		}
	}

}
//return a data that can be used to load forge maps in future
char* Forge::Generate_Forge_Data(char* map_name, char *description)
{
	int total_size = FORGE_MAP_HEADER_SIZE + SCNR_HEADER_SIZE + *net_game_equip_count * 0x90;
	//i call it partial because it contains
	char *partial_scnr = new char[total_size];

	wchar_t *scnr_name = (wchar_t*)(*(DWORD*)(game.GetBase() + 0x420FE8) + 0x4CBC);

	memcpy(partial_scnr, scnr_name, 128);//we copy the scenario name(unicode)
	memcpy(partial_scnr + 128, map_name, 16);//then we copy the map_name

	if (sizeof(description) < FORGE_MAP_HEADER_SIZE-134)//then we copy the description
	{
		memcpy(partial_scnr + 134, description, sizeof(description));
	}
	else memcpy(partial_scnr + 134, "Desciption Length too long", sizeof(description));

	//Then we write out stuff
	//***Net Game stuff
	*(DWORD*)(partial_scnr + FORGE_MAP_HEADER_SIZE + 0x120) = *net_game_equip_count;//we write the count
	//then we copy our stuff
	memcpy(partial_scnr + FORGE_MAP_HEADER_SIZE + SCNR_HEADER_SIZE, net_game_equip_array, *net_game_equip_count * 0x90);
	//write an offset for it
	*(DWORD*)(partial_scnr + FORGE_MAP_HEADER_SIZE + 0x124) = FORGE_MAP_HEADER_SIZE + SCNR_HEADER_SIZE;

	return partial_scnr;
}

void Forge::teleport_object_to_player_cam(BYTE player_index)
{
	cartessian_co_ord my_sys;

	//**** FIX these stuff so that they refer to each player individualy

	my_sys.cam_x = *(float*)(game.GetBase() + 0x4A8504);
	my_sys.cam_y = *(float*)(game.GetBase() + 0x4A8508);
	my_sys.cam_z = *(float*)(game.GetBase() + 0x4A850C);

	my_sys.alpha = *(float*)(game.GetBase() + 0x4A852C);
	my_sys.beta = *(float*)(game.GetBase() + 0x4A8530);
	my_sys.gamma = *(float*)(game.GetBase() + 0x4A8534);

	my_sys.i_obj_X = range[player_index] * my_sys.alpha;
	my_sys.i_obj_Y = range[player_index] * my_sys.beta;
	my_sys.i_obj_Z = range[player_index] * my_sys.gamma;

	my_sys.obj_x = my_sys.cam_x + my_sys.i_obj_X;
	my_sys.obj_y = my_sys.cam_y + my_sys.i_obj_Y;
	my_sys.obj_z = my_sys.cam_z + my_sys.i_obj_Z;

	float* loc = new float[3];
	*((float*)loc) = my_sys.obj_x;
	*((float*)loc + 1) = my_sys.obj_y;
	*((float*)loc + 2) = my_sys.obj_z;

	game.object_set_position(net_game_manip_data[player_index]->ingamedatum,loc ,0);
	
}





