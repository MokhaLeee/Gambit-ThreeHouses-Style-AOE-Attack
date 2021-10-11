#include "../../GambitCore.h"
void MakeTargetListFor_SubGambitMenu(Unit* unit,u8 range){
	InitTargets(unit->xPos,unit->yPos);
	BmMapFill(gMapRange,0);
	MapIncInBoundedRange(unit->xPos,unit->yPos,0,range);
	ForEachUnitInRange(AddUnitToTargetListIfNotAllied);
	
	return;
}

void MakeTargetListFor_AfterSelectAPressed(u8 x, u8 y, u8 GambitIndex){
	InitTargets(x,y);
	gpSubjectMap = &gMapMovement;
	ForEachUnitInRange_ByRangeMovement(AddUnitToTargetListIfNotAllied);
	return;
}

void ForEachUnitInRange_ByRangeMovement(void(func)(struct Unit*)){
	if( (gMapSize.x<0) | (gMapSize.y<0) )
		return;
	
	for( u8 y=0; y<gMapSize.y; y++ )
		for( u8 x=0; x<gMapSize.x; x++ )
		{
			if( -1 == gMapMovement[y][x] )
				continue;
			if( gMapUnit[y][x] )
				func( GetUnit(gMapUnit[y][x]) );
		}
	return;
}




// Funcs
void _TargetSelect_Gambit4_TargetChange(struct TargetSelectionProc* proc, struct TargetEntry* entry){
		
	FillAOEEffectMay_OnChangeTarget(entry->x,entry->y,0);
	BmMapFill(gMapRange,0);
	FillRangeMapForHover(gActiveUnit,2);
		
	Proc* pproc = ProcFind(gProc_MoveLimitView);
	if( pproc )
		*((u16*)pproc+0x4A/2) = 0x24; 	//Load Red&Green(need new-MapDisplay)
	DisplayMoveRangeGraphics(0x3);
	
	TargetSelect_ChangeTarget(proc,entry);
	return;
}


int _TargetSelect_Gambit5_APressed(struct TargetSelectionProc* proc, struct TargetEntry* entry){
	gActionData.unitActionType = Gambit_ActionIndex;
	gActionData.targetIndex = entry->unitIndex;
	
	EndEachProc(gProc_BkSel);
	MakeTargetListFor_AfterSelectAPressed(entry->x,entry->y,0);
	
	SaveTarget_PostGambitTargetSelection();
	return TSE_CLEAR_GFX | TSE_PLAY_BEEP | TSE_END | TSE_DISABLE;
}


int _TargetSelect_Gambit6_BPressed(struct TargetSelectionProc* proc, struct TargetEntry* entry){
	_ResetIconGraphics();
	LoadIconPalettes(0x4);
	StartMenu(GambitSelectMenu);
	return TSE_CLEAR_GFX | TSE_PLAY_BEEP | TSE_END | TSE_DISABLE;
}

