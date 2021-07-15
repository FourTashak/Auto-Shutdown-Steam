#pragma once

#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

DWORD GetProcId(const wchar_t* procName);

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);

void ItemsInQue(System::Windows::Forms::Label^ Label2);

bool kapat = false;

bool color = false; //False = Red, Green = True

bool OnOff = false; //False = off, True = on

bool onoff2 = false;