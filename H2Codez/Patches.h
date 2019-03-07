#pragma once
#include "stdafx.h"


VOID WriteBytesASM(DWORD destAddress, LPVOID patch, DWORD numBytes);

VOID PatchCall(DWORD call_addr, DWORD new_function_ptr);


