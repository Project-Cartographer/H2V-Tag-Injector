#include "stdafx.h"
#include "ToolCommandDefinitions.inl"


VOID WriteBytesASM_2(DWORD destAddress, LPVOID patch, DWORD numBytes)
{
	DWORD oldProtect = 0;
	DWORD srcAddress = PtrToUlong(patch);

	VirtualProtect((void*)(destAddress), numBytes, PAGE_EXECUTE_READWRITE, &oldProtect);

	__asm
	{
		nop
		nop
			nop

			mov esi, srcAddress
			mov edi, destAddress
			mov ecx, numBytes
			Start :
		cmp ecx, 0
			jz Exit

			mov al, [esi]
			mov[edi], al
			dec ecx
			inc esi
			inc edi
			jmp Start
			Exit :
		nop
			nop
			nop
	}

	VirtualProtect((void*)(destAddress), numBytes, oldProtect, &oldProtect);
}


static const s_tool_command* h2tool_extra_commands[] = { 
	&import_model_render,
	&import_model_collision,
	&import_model_physics,
	&import_model,
	&import_model_animations,
	import_class_monitor_structures,
	import_class_monitor_bitmaps,
	&import_sound,
	&tool_build_structure_from_jms,

};

int __cdecl s_tool_command_compare(void *, const void* lhs, const void* rhs)
{
	const s_tool_command* _lhs = *CAST_PTR(const s_tool_command* const*, lhs);
	const s_tool_command* _rhs = *CAST_PTR(const s_tool_command* const*, rhs);

	const wchar_t* l = _lhs->name;
	const wchar_t* r = _rhs->name;
	if (l[0] == L'~') l++;
	if (r[0] == L'~') r++;

	return _wcsicmp(l, r);
}
void H2Tool_Extras::Increase_structure_size_Check()
{

	BYTE Size_Patch[4] = { 0xF2,0xF2,0xF2,0x0F };

	WriteBytesASM_2(0x41F83A, Size_Patch, 4);

}
void _H2ToolAttachHooks()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());


	//  DetourAttach(&(PVOID&)pPlayerSpeed,OnPlayerSpeed);	

	//  DetourAttach(&(PVOID&)pcreatechar,h_CreateCharacter);
	//DetourAttach(&(PVOID&)pXYZ, h_XYZUpdate);


	DetourTransactionCommit();
	return;
}
void _H2ToolDetachHooks()
{
	//DetourDetach(&(PVOID&)pgameoptions,h_GetGameOptions);
	// DetourDetach(&(PVOID&)pMapSelect,h_MPMapSelect);
	// DetourDetach(&(PVOID&)psquadsettings,h_SquadSettings);	
	return;
}

void H2Tool_Extras::Initialize()
{
	H2PCTool.WriteLog("Dll Successfully Injected to H2Tool");
	game.g_base = GetModuleHandleW(L"H2Tool.exe");
	halo.H2Type = ProcessType::H2Tool;

	this->Increase_structure_size_Check();
	this->AddExtraCommands();
}

void H2Tool_Extras::AddExtraCommands()
{
	H2PCTool.WriteLog("Adding Extra Commands to H2Tool");
#pragma region New Function Defination Creation 

	BYTE k_number_of_tool_commands = 0xC;
	BYTE k_number_of_tool_commands_new = 0xC + NUMBEROF(h2tool_extra_commands);

	// Tool's original tool commands
	static const s_tool_command* const* tool_import_classes = CAST_PTR(s_tool_command**, 0x97B6EC);
	// The new tool commands list which is made up of tool's
	// and [yelo_extra_tool_commands]
	static s_tool_command* tool_commands[0xC + NUMBEROF(h2tool_extra_commands)];

	// copy official tool commands
	memcpy_s(tool_commands, sizeof(tool_commands),
		tool_import_classes, sizeof(s_tool_command*) * k_number_of_tool_commands);
	// copy yelo tool commands
	memcpy_s(&tool_commands[k_number_of_tool_commands], sizeof(h2tool_extra_commands),
		h2tool_extra_commands, sizeof(h2tool_extra_commands));
	// Now I know my ABCs
	qsort_s(tool_commands, NUMBEROF(tool_commands), sizeof(s_tool_command*), s_tool_command_compare, NULL);
#pragma endregion
#pragma region UpdateTool_function References
	// update references to the tool command definitions

	///Old Logic
	//for (int x = 0; x < NUMBEROF(tool_commands_references); x++)			*tool_commands_references[x] = &tool_commands[0];



	DWORD new_tool_defination_Table_address = (DWORD)&tool_commands[0];

	H2PCTool.WriteLog("New Tool_Definations Addy : %0X", new_tool_defination_Table_address);
	///New Logic
	DWORD c = new_tool_defination_Table_address;
	BYTE *f = (BYTE*)(&c);
	BYTE Reference_Patch[4] = { f[0],f[1],f[2],f[3]};//move to ecx		

	WriteBytesASM_2(0x410596, Reference_Patch, 4);
	WriteBytesASM_2(0x41060E, Reference_Patch, 4);
	WriteBytesASM_2(0x412D86, Reference_Patch, 4);

	H2PCTool.WriteLog("Reversed : %0X %0X %0X %0X", f[0], f[1], f[2], f[3]);

#pragma endregion
#pragma region UpdateTool_functionCount References
	// update code which contain the tool command definitions count

	///Old Logic
	//for (int x = 0; x < NUMBEROF(tool_commands_count); x++)				*tool_commands_count[x] = NUMBEROF(tool_commands);





   ///New Logic
	BYTE Count_Patch[1] = {k_number_of_tool_commands_new}; // cmp     si, 0Ch 

	WriteBytesASM_2(0x4105E5, Count_Patch, 1);
	WriteBytesASM_2(0x412D99, Count_Patch, 1);
#pragma endregion
}