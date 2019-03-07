#include "stdafx.h"
#include "Net_Game_Equipment.h"


//Constructor
Net_Game_Equipment::Net_Game_Equipment(char* data)
{
	//intialise some bunch of data
	//this->ingamedatum = ingamedatum;
	this->data = data;
}
//Destructor
Net_Game_Equipment::~Net_Game_Equipment()
{
	delete data;
}

//Gets the datum index of the tag linked to the itemcollection of the concerned Net_Game_Equipment field
DWORD Net_Game_Equipment::Get_datum_index()
{
	DWORD TagTableStart = *(DWORD*)(game.GetBase() + 0x47CD50);
	DWORD MapMemBase = *(DWORD*)(game.GetBase() + 0x47CD64);

	DWORD itmc_datum_index = *(DWORD*)(data + 0x5C);//the datum index of the itmc
	DWORD itmc_memaddr = *(DWORD*)(TagTableStart + ((itmc_datum_index & 0xFFFF) * 0x10) + 0x8);//scnr index is 0x0 in most cases

	return *(DWORD*)(MapMemBase + itmc_memaddr + 0x14);//i only care about the first permutation
}
//Syncs the position and orientation of the ingame equipment with the netgame data

void Net_Game_Equipment::Sync_data_and_equip()
{
	auto objDynamic = GetObjectDynamic(this->ingamedatum);
	if (objDynamic != -1)
	{
		*(float*)(this->data + 0x40) = *(float*)(objDynamic + 0x64);//Object X to NetGame X
		*(float*)(this->data + 0x44) = *(float*)(objDynamic + 0x68);//Object Y to NetGame Y
		*(float*)(this->data + 0x48) = *(float*)(objDynamic + 0x6C);//Object Z to NetGame Z
		*(float*)(this->data + 0x4C) = *(float*)(objDynamic + 0x70);//Object I to NetGame I
		*(float*)(this->data + 0x50) = *(float*)(objDynamic + 0x74);//Object J to NetGame J
		*(float*)(this->data + 0x54) = *(float*)(objDynamic + 0x78);//Object K to NetGame K		
	}
}

//some other functions
DWORD GetObjectDynamic(DWORD datum)
{
	if (datum != -1)
		return
		*(DWORD *)(*(DWORD *)(DYNAMIC_OBJECT_BASE + 68) + 12 * (unsigned __int16)datum + 8);

	return -1;

}
