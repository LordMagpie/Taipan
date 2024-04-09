// Globals.h

#pragma once
#define ULL unsigned long long
#define LL long long

#include <string>

using std::string;

struct TextSize {
	int width;
	int height;
};

extern string FirmName;
extern ULL HoldTotal;
extern LL HoldFree;
extern unsigned int Guns;
extern ULL HoldOpium, HoldSilk, HoldArms, HoldGeneral;
extern ULL WarehouseTotal, WarehouseFree, WarehouseUsed;
extern ULL WarehouseOpium, WarehouseSilk;
extern ULL WarehouseArms, WarehouseGeneral;
extern string LocationNanmes[8];
extern string Months[12];
extern unsigned int Location;
extern unsigned int Month, Year;
extern ULL Cash, Bank, Debt;
extern int ShipStatus;
extern string ShipStatusText[6];
extern int FH1;
extern int FH2;
extern int FT1;
extern string FontFilename;