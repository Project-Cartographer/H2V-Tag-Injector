#include "stdafx.h"
#include "Global_consts.h"

#pragma once


class Net_Game_Equipment
{

public:
	char* data;
	DWORD ingamedatum;

	DWORD Get_datum_index();
	void Sync_data_and_equip();

	Net_Game_Equipment(char *data);
	~Net_Game_Equipment();

};

DWORD GetObjectDynamic(DWORD datum);