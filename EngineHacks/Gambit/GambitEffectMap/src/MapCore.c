#include "../../GambitCore.h"

void FillRangeMapForHover(Unit* unit,u8 range){
	MapAddInRange(unit->xPos, unit->yPos, range, 1);
	MapAddInRange(unit->xPos, unit->yPos, 0, -1);
	return;
}


void FillAOEEffectMay_OnChangeTarget(u8 x, u8 y, u8 GambitIndex){
	u8 uDirec = GetFacingDirection(gActiveUnit->xPos, gActiveUnit->yPos, x, y);
	GambitEffectMap_DrawMapRoutineTable[0](x,y,uDirec);
	return;
}


void GambitResetMaps(void){
	BmMapFill(gMapMovement,-1);
	BmMapFill(gMapMovement2,-1);
	BmMapFill(gMapRange,0);
	gpSubjectMap = &gMapMovement;
	DisplayMoveRangeGraphics(0x3);
	HideMoveRangeGraphicsWrapper();
	return;
}