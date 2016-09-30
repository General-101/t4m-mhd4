// ==========================================================
// T4M project
// 
// Component: clientdll
// Purpose: Increasing memory pool sizes
//
// Initial author: TheApadayo
//
// Started: 2015-07-18
// ==========================================================

#include "StdInc.h"

void PatchT4_MemoryLimits(int FXLimit, int IMAGELimit, int SOUNDLimit, int MATERIALLimit, int STRINGTABLELimit, int WEAPONLimit, int XMODELLimit)
{
	// increase pool sizes to similar (or greater) t5 sizes.
	ReallocateAssetPool(ASSET_TYPE_FX, FXLimit);
	ReallocateAssetPool(ASSET_TYPE_IMAGE, IMAGELimit);
	ReallocateAssetPool(ASSET_TYPE_LOADED_SOUND, SOUNDLimit);
	ReallocateAssetPool(ASSET_TYPE_MATERIAL, MATERIALLimit);
	ReallocateAssetPool(ASSET_TYPE_STRINGTABLE, STRINGTABLELimit);
	ReallocateAssetPool(ASSET_TYPE_WEAPON, WEAPONLimit);
	ReallocateAssetPool(ASSET_TYPE_XMODEL, XMODELLimit);


	// change the size of g_mem from 0x12C00000 to 0x14800000 (what it is in t5)
	*(DWORD*)0x5F5492 = 0x19600000;
	*(DWORD*)0x5F54D1 = 0x19600000;
	*(DWORD*)0x5F54DB = 0x19600000;
}