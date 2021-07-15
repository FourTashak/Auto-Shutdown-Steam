#pragma once
#include "windows.h"
#include "fDec.h"
#include "Source.h"
#include "MyForm2.h"

DWORD GetProcId(const wchar_t* procName)
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!_wcsicmp(procEntry.szExeFile, procName))
				{
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;
}

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}
	return addr;
}

int Autoshutdown()
{
	int queValue = 0;

	DWORD procid = GetProcId(L"steam.exe"); //Gets steams Process ID
	uintptr_t modulebase = GetModuleBaseAddress(procid, L"tier0_s.dll"); //Gets the steamui.dll's base address

	HANDLE hprocess = 0;
	hprocess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procid);

	uintptr_t baseAddress = modulebase + 0x000934EC;

	std::vector<unsigned int> queOffsets = { 0x18, 0x14, 0x14, 0xD8, 0xE0, 0x0, 0x0 };
	uintptr_t queAddr = FindDMAAddy(hprocess, baseAddress, queOffsets);

	while (true)
	{
		if (kapat == true)
		{
			break;
		}

		ReadProcessMemory(hprocess, (BYTE*)queAddr, &queValue, sizeof(queValue), nullptr);

		if (queValue==0)
		{
			system("C:\\WINDOWS\\System32\\shutdown -s");
			break;
		}
		Sleep(1000);
	}
	return 0;
}

int ItemsInQue(int queNumber)
{
	int queValue=0;

	DWORD procid = GetProcId(L"steam.exe"); //Gets steams Process ID
	uintptr_t modulebase = GetModuleBaseAddress(procid, L"steamui.dll"); //Gets the steamui.dll's base address

	HANDLE hprocess = 0;
	hprocess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procid);

	uintptr_t baseAddress = modulebase + 0x00B945F8;

	std::vector<unsigned int> queOffsets = { 0x74, 0x4, 0x180, 0xc0, 0xe0, 0x0, 0x0 };
	uintptr_t queAddr = FindDMAAddy(hprocess, baseAddress, queOffsets);

	while (true)
	{
		ReadProcessMemory(hprocess, (BYTE*)queAddr, &queValue, sizeof(queValue), nullptr);
		return queValue;
		Sleep(1000);
	}
}
