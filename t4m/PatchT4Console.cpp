// ==========================================================
// T4M project
// 
// Component: clientdll
// Purpose: Changes/functionality related to console.
//
// Initial author: DidUknowiPwn
// Started: 2015-07-12
// ==========================================================

#include "StdInc.h"
#include <fstream>
#include <string>

void FilterConsoleSpam();
dvar_t* con_external;

void PatchT4_Console(int EnableConsole)
{
	//强制开启游戏内控制台
	*(BYTE*)0x4781FE = 0xEB;
	FilterConsoleSpam();
	if (EnableConsole == 1)
	{
		Sys_ShowConsole();
	}
}

void Sys_ShowConsole()
{
	DWORD func = 0x6057F0;
	__asm
	{
		call func
	}
}

void FilterConsoleSpam()
{
	PatchMemory(0x84B670, (PBYTE)"", 2); // set "." to blank since it spams it in dwLogOnComplete
	nop(0x5F9DF2, 5); 
	
    // 关闭 "Failed to log on" (引起吊针)
	nop(0x5FC93D, 5); 
	nop(0x5FC9CD, 5); 
	// 关闭脚本错误(引起吊针)
	nop(0x68B202, 5);
	nop(0x68B220, 5);
	nop(0x68B255, 5);
	nop(0x68B240, 5);
	nop(0x68B22A, 5);

	// 关闭声音错误(引起吊针)
	nop(0x6B6728, 5);
	
	nop(0x5F9E2F, 5); // disable DebugReportProfileDVars call (was being spammed when in lobbies and such)
	nop(0x5A3C44, 5); // disable Com_Printf call for "ragdoll allocation failed" (causes frame drops up the ass)
	nop(0x57B15B, 5); // disable Com_Printf call for "g_numFriends is now %i" (internal)
	nop(0x57FE59, 5); // disable Com_Printf call for "nulling invite info for friend %s"
	nop(0x57FE15, 5); // disable Com_Printf call for "updating profile info for friend %s"
}
