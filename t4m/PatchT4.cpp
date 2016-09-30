// ==========================================================
// T4M project
// 
// Component: clientdll
// Purpose: World at War patches
//
// Initial author: UNKNOWN
// Started: 2015-07-08
// ==========================================================

#include <string>
#include "StdInc.h"

void loadGameOverlay();
void PatchT4();
void PatchT4_MemoryLimits(int FXLimit, int IMAGELimit, int SOUNDLimit, int MATERIALLimit, int STRINGTABLELimit, int WEAPONLimit, int XMODELLimit);
void PatchT4_Branding(int DisableOnline,int DisableIntroVideo);
void PatchT4_Console(int EnableConsole);
void PatchT4_Dvars();
void PatchT4_NoBorder();
void PatchT4_PreLoad(int RemoveOptimal, int SkipSafeModeCheck);
void PatchT4_SteamDRM();
void PatchT4_FileDebug();
using namespace std;


void Sys_RunInit()
{
	PatchT4();
}

void PatchT4()
{
	// ↓ 这个造成服务器验证失败？
	//PatchT4_SteamDRM();

	//加载配置文件
	std::string ifile(".\\t4m.ini"), tmp;
	std::ifstream ifs(ifile.c_str());
	LPTSTR lpPath = new char[MAX_PATH];
	strcpy(lpPath, ".\\t4m.ini");
	if (!ifs)
	{
		WritePrivateProfileString("T4MCFG", "RemoveOptimal", "0", lpPath);
		WritePrivateProfileString("T4MCFG", "SkipSafeModeCheck", "1", lpPath);
		WritePrivateProfileString("T4MCFG", "EnableConsole", "0", lpPath);
		WritePrivateProfileString("T4MCFG", "DisableOnline", "1", lpPath);
		WritePrivateProfileString("T4MCFG", "DisableIntroVideo", "1", lpPath);
		WritePrivateProfileString("T4MCFG", "Windowed", "0", lpPath);
		WritePrivateProfileString("T4MLimits", "FXLimit", "600", lpPath);
		WritePrivateProfileString("T4MLimits", "IMAGELimit", "4096", lpPath);
		WritePrivateProfileString("T4MLimits", "SOUNDLimit", " 2400", lpPath);
		WritePrivateProfileString("T4MLimits", "MATERIALLimit", "4096", lpPath);
		WritePrivateProfileString("T4MLimits", "STRINGTABLELimit", "80", lpPath);
		WritePrivateProfileString("T4MLimits", "WEAPONLimit", "320", lpPath);
		WritePrivateProfileString("T4MLimits", "XMODELLimit", "1500", lpPath);
		WritePrivateProfileString("T4MCFG", "LoadSteamOverlay", "1", lpPath);
		PatchT4_MemoryLimits(600, 4096, 2400, 4096, 80, 320, 1500);
		PatchT4_Branding(1, 1);
		PatchT4_Console(0);
		PatchT4_Dvars();
		PatchT4_NoBorder();
		PatchT4_PreLoad(0, 1);
		if (!GetModuleHandle("gameoverlayrenderer.dll"))
			loadGameOverlay();
	}
	else
	{
		int RemoveOptimal;
		int SkipSafeModeCheck;
		int EnableConsole;
		int DisableOnline;
		int DisableIntroVideo;
		int FXLimit;
		int IMAGELimit;
		int SOUNDLimit;
		int MATERIALLimit;
		int STRINGTABLELimit;
		int WEAPONLimit;
		int XMODELLimit;
		RemoveOptimal = GetPrivateProfileInt("T4MCFG", "RemoveOptimal", 0, lpPath);
		SkipSafeModeCheck = GetPrivateProfileInt("T4MCFG", "SkipSafeModeCheck", 0, lpPath);
		EnableConsole = GetPrivateProfileInt("T4MCFG", "EnableConsole", 0, lpPath);
		DisableOnline = GetPrivateProfileInt("T4MCFG", "DisableOnline", 0, lpPath);
		DisableIntroVideo = GetPrivateProfileInt("T4MCFG", "DisableIntroVideo", 0, lpPath);
		FXLimit = GetPrivateProfileInt("T4MLimits", "FXLimit", 0, lpPath);
		IMAGELimit = GetPrivateProfileInt("T4MLimits", "IMAGELimit", 0, lpPath);
		SOUNDLimit = GetPrivateProfileInt("T4MLimits", "SOUNDLimit", 0, lpPath);
		MATERIALLimit = GetPrivateProfileInt("T4MLimits", "MATERIALLimit", 0, lpPath);
		STRINGTABLELimit = GetPrivateProfileInt("T4MLimits", "STRINGTABLELimit", 0, lpPath);
		WEAPONLimit = GetPrivateProfileInt("T4MLimits", "WEAPONLimit", 0, lpPath);
		XMODELLimit = GetPrivateProfileInt("T4MLimits", "XMODELLimit", 0, lpPath);
		PatchT4_MemoryLimits(FXLimit, IMAGELimit, SOUNDLimit, MATERIALLimit, STRINGTABLELimit, WEAPONLimit, XMODELLimit);
		PatchT4_Branding(DisableOnline, DisableIntroVideo);
		PatchT4_Console(EnableConsole);
		PatchT4_Dvars();
		PatchT4_NoBorder();
		PatchT4_PreLoad(RemoveOptimal, SkipSafeModeCheck);
		if (GetPrivateProfileInt("T4MCFG", "Windowed", 0, lpPath) == 1)
		//一个投机取巧的窗口化方法#滑稽
			*(DWORD*)0x6D6111 = (DWORD)"r_windowed";
		if (GetPrivateProfileInt("T4MCFG", "LoadSteamOverlay", 0, lpPath) == 1)
			//加载Sbeam Overlay
			if (!GetModuleHandle("gameoverlayrenderer.dll"))
				loadGameOverlay();
	}
	delete[] lpPath;

	//改个标题压压惊
	*(DWORD*)0x6D65A0 = (DWORD)"Call of Duty: World at War Campaign/Coop - T4M MHD4 Editon";
	
	//PatchT4_FileDebug();
	
}

void PatchT4_PreLoad(int RemoveOptimal,int SkipSafeModeCheck)
{
	//这里是去掉那几个框
	// ↓ 导致我分辨率和抗狗牙一直变回默认的罪魁祸首,T4M将其去掉却导致直接帮我点了是(cao)
	if (RemoveOptimal == 1)
	{
		nop(0x5FE685, 5);
	}
	if (SkipSafeModeCheck == 1)
	{
		*(BYTE*)0x5FF386 = (BYTE)0xEB;
	}
}

void PatchT4_SteamDRM()
{
	// Replace encrypted .text segment
	DWORD size = 0x3EA000;
	std::string data = GetBinaryResource(IDB_TEXT);
	uncompress((unsigned char*)0x401000, &size, (unsigned char*)data.data(), data.size());

	// Apply new entry point
	HMODULE hModule = GetModuleHandle(NULL);
	PIMAGE_DOS_HEADER header = (PIMAGE_DOS_HEADER)hModule;
	PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)((DWORD)hModule + header->e_lfanew);
	ntHeader->OptionalHeader.AddressOfEntryPoint = 0x3AF316;
}

//code from https://github.com/momo5502/cod-mod/
void loadGameOverlay()
{
	try
	{
		std::string m_steamDir;
		HKEY hRegKey;

		if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\Valve\\Steam", 0, KEY_QUERY_VALUE, &hRegKey) == ERROR_SUCCESS)
		{
			char pchSteamDir[MAX_PATH];
			DWORD dwLength = sizeof(pchSteamDir);
			RegQueryValueExA(hRegKey, "InstallPath", NULL, NULL, (BYTE*)pchSteamDir, &dwLength);
			RegCloseKey(hRegKey);

			m_steamDir = pchSteamDir;
		}

		//Com_Printf(0, "Loading %s\\gameoverlayrenderer.dll...\n", m_steamDir.c_str());
		HMODULE overlay = LoadLibrary(va("%s\\gameoverlayrenderer.dll", m_steamDir.c_str()));

		if (overlay)
		{
			FARPROC _SetNotificationPosition = GetProcAddress(overlay, "SetNotificationPosition");

			if (_SetNotificationPosition)
			{
				((void(*)(uint32_t))_SetNotificationPosition)(1);
			}
		}
	}
	catch (int e)
	{
		//Com_Printf(0, "Failed to inject Steam's gameoverlay: %d", e);
	}
}
