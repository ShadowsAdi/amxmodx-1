

#include "amxxmodule.h"
#include "rank.h"


static cell AMX_NATIVE_CALL get_user_astats(AMX *amx, cell *params) /* 6 param */
{
	int index = params[1];
	if (index<1||index>gpGlobals->maxClients){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}
	int attacker = params[2];
	if (attacker<0||attacker>gpGlobals->maxClients){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}
	CPlayer* pPlayer = GET_PLAYER_POINTER_I(index);
	if (pPlayer->attackers[attacker].hits){
		cell *cpStats = MF_GetAmxAddr(amx,params[3]);
		cell *cpBodyHits = MF_GetAmxAddr(amx,params[4]);
		CPlayer::PlayerWeapon* stats = &pPlayer->attackers[attacker];
		cpStats[0] = stats->kills;
		cpStats[1] = stats->deaths;
		cpStats[2] = stats->hs;
		cpStats[3] = stats->tks;
		cpStats[4] = stats->shots;
		cpStats[5] = stats->hits;
		cpStats[6] = stats->damage;
		for(int i = 1; i < 8; ++i)
			cpBodyHits[i] = stats->bodyHits[i];
		if (params[6] && attacker && stats->name )
			MF_SetAmxString(amx,params[5],stats->name,params[6]);
		return 1;
	}
	return 0;
}

static cell AMX_NATIVE_CALL get_user_vstats(AMX *amx, cell *params) /* 6 param */
{
	int index = params[1];
	if (index<1||index>gpGlobals->maxClients){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}
	int victim = params[2];
	if (victim<0||victim>gpGlobals->maxClients){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}
	CPlayer* pPlayer = GET_PLAYER_POINTER_I(index);
	if (pPlayer->victims[victim].hits){
		cell *cpStats = MF_GetAmxAddr(amx,params[3]);
		cell *cpBodyHits = MF_GetAmxAddr(amx,params[4]);
		CPlayer::PlayerWeapon* stats = &pPlayer->victims[victim];
		cpStats[0] = stats->kills;
		cpStats[1] = stats->deaths;
		cpStats[2] = stats->hs;
		cpStats[3] = stats->tks;
		cpStats[4] = stats->shots;
		cpStats[5] = stats->hits;
		cpStats[6] = stats->damage;
		for(int i = 1; i < 8; ++i)
			cpBodyHits[i] = stats->bodyHits[i];
		if (params[6] && victim && stats->name)
			MF_SetAmxString(amx,params[5],stats->name,params[6]);
		return 1;
	}
	return 0;
}

static cell AMX_NATIVE_CALL get_user_wrstats(AMX *amx, cell *params) /* 4 param */ // DEC-Weapon (round) stats (end)
{
	int index = params[1];
	if (index<1||index>gpGlobals->maxClients){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}
	int weapon = params[2];
	if (weapon<0||weapon>=MAX_WEAPONS){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}
	CPlayer* pPlayer = GET_PLAYER_POINTER_I(index);
	if (pPlayer->weaponsRnd[weapon].shots){
		cell *cpStats = MF_GetAmxAddr(amx,params[3]);
		cell *cpBodyHits = MF_GetAmxAddr(amx,params[4]);
		Stats* stats = &pPlayer->weaponsRnd[weapon];
		cpStats[0] = stats->kills;
		cpStats[1] = stats->deaths;
		cpStats[2] = stats->hs;
		cpStats[3] = stats->tks;
		cpStats[4] = stats->shots;
		cpStats[5] = stats->hits;
		cpStats[6] = stats->damage;
		for(int i = 1; i < 8; ++i)
			cpBodyHits[i] = stats->bodyHits[i];
		return 1;
	}
	return 0;
}

static cell AMX_NATIVE_CALL get_user_wstats(AMX *amx, cell *params) /* 4 param */
{
	int index = params[1];
	if (index<1||index>gpGlobals->maxClients){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}
	int weapon = params[2];
	if (weapon<0||weapon>=MAX_WEAPONS){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}
	CPlayer* pPlayer = GET_PLAYER_POINTER_I(index);
	if (pPlayer->weapons[weapon].shots){
		cell *cpStats = MF_GetAmxAddr(amx,params[3]);
		cell *cpBodyHits = MF_GetAmxAddr(amx,params[4]);
		CPlayer::PlayerWeapon* stats = &pPlayer->weapons[weapon];
		cpStats[0] = stats->kills;
		cpStats[1] = stats->deaths;
		cpStats[2] = stats->hs;
		cpStats[3] = stats->tks;
		cpStats[4] = stats->shots;
		cpStats[5] = stats->hits;
		cpStats[6] = stats->damage;
		for(int i = 1; i < 8; ++i)
			cpBodyHits[i] = stats->bodyHits[i];
		return 1;
	}
	return 0;
}

static cell AMX_NATIVE_CALL reset_user_wstats(AMX *amx, cell *params) /* 6 param */
{
	int index = params[1];
	if (index<1||index>gpGlobals->maxClients){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}
	GET_PLAYER_POINTER_I(index)->restartStats();
	return 1;
}

static cell AMX_NATIVE_CALL get_user_rstats(AMX *amx, cell *params) /* 3 param */
{
	int index = params[1];
	if (index<1||index>gpGlobals->maxClients){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}
	CPlayer* pPlayer = GET_PLAYER_POINTER_I(index);
	if (pPlayer->rank){
		cell *cpStats = MF_GetAmxAddr(amx,params[2]);
		cell *cpBodyHits = MF_GetAmxAddr(amx,params[3]);
		cpStats[0] = pPlayer->life.kills;
		cpStats[1] = pPlayer->life.deaths;
		cpStats[2] = pPlayer->life.hs;
		cpStats[3] = pPlayer->life.tks;
		cpStats[4] = pPlayer->life.shots;
		cpStats[5] = pPlayer->life.hits;
		cpStats[6] = pPlayer->life.damage;
		for(int i = 1; i < 8; ++i)
			cpBodyHits[i] = pPlayer->life.bodyHits[i];
		return 1;
	}
	return 0;
}

static cell AMX_NATIVE_CALL get_user_stats(AMX *amx, cell *params) /* 3 param */
{
	int index = params[1];
	if (index<1||index>gpGlobals->maxClients){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}
	CPlayer* pPlayer = GET_PLAYER_POINTER_I(index);
	if ( pPlayer->rank ){
		cell *cpStats = MF_GetAmxAddr(amx,params[2]);
		cell *cpBodyHits = MF_GetAmxAddr(amx,params[3]);
		cpStats[0] = pPlayer->rank->kills;
		cpStats[1] = pPlayer->rank->deaths;
		cpStats[2] = pPlayer->rank->hs;
		cpStats[3] = pPlayer->rank->tks;
		cpStats[4] = pPlayer->rank->shots;
		cpStats[5] = pPlayer->rank->hits;
		cpStats[6] = pPlayer->rank->damage;

		cpStats[7] = pPlayer->rank->getPosition();

		for(int i = 1; i < 8; ++i)
			cpBodyHits[i] = pPlayer->rank->bodyHits[i];
		return pPlayer->rank->getPosition();
	}
	return 0;

}

static cell AMX_NATIVE_CALL get_user_stats2(AMX *amx, cell *params) /* 3 param */
{
	int index = params[1];
	if (index<1||index>gpGlobals->maxClients){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}
	CPlayer* pPlayer = GET_PLAYER_POINTER_I(index);
	if ( pPlayer->rank ){
		cell *cpStats = MF_GetAmxAddr(amx,params[2]);

		cpStats[0] = pPlayer->rank->bDefusions;
		cpStats[1] = pPlayer->rank->bDefused;
		cpStats[2] = pPlayer->rank->bPlants;
		cpStats[3] = pPlayer->rank->bExplosions;

		return pPlayer->rank->getPosition();
	}
	return 0;
}

static cell AMX_NATIVE_CALL get_stats(AMX *amx, cell *params) /* 3 param */
{
	
	int index = params[1] + 1;

	for(RankSystem::iterator a = g_rank.front(); a ;--a){
		if ((*a).getPosition() == index)  {
			cell *cpStats = MF_GetAmxAddr(amx,params[2]);
			cell *cpBodyHits = MF_GetAmxAddr(amx,params[3]);
			cpStats[0] = (*a).kills;
			cpStats[1] = (*a).deaths;
			cpStats[2] = (*a).hs;
			cpStats[3] = (*a).tks;
			cpStats[4] = (*a).shots;
			cpStats[5] = (*a).hits;
			cpStats[6] = (*a).damage;

			cpStats[7] = (*a).getPosition();

			MF_SetAmxString(amx,params[4],(*a).getName(),params[5]);
			for(int i = 1; i < 8; ++i)
				cpBodyHits[i] = (*a).bodyHits[i];
			return --a ? index : 0;
		}	
	}
	
	return 0;
}

static cell AMX_NATIVE_CALL get_stats2(AMX *amx, cell *params) /* 3 param */
{
	
	int index = params[1] + 1;

	for(RankSystem::iterator a = g_rank.front(); a ;--a){
		if ((*a).getPosition() == index)  {
			cell *cpStats = MF_GetAmxAddr(amx,params[2]);

			cpStats[0] = (*a).bDefusions;
			cpStats[1] = (*a).bDefused;
			cpStats[2] = (*a).bPlants;
			cpStats[3] = (*a).bExplosions;

			return --a ? index : 0;
		}	
	}
	
	return 0;
}

static cell AMX_NATIVE_CALL get_statsnum(AMX *amx, cell *params)
{
	return g_rank.getRankNum();
}

static cell AMX_NATIVE_CALL register_cwpn(AMX *amx, cell *params){ // name,logname,melee=0 
	int i;
	bool bFree = false;
	for ( i=MAX_WEAPONS;i<MAX_WEAPONS+MAX_CWEAPONS;i++){
		if ( !weaponData[i].ammoSlot ){
			bFree = true;
			break;
		}
	}

	if ( !bFree ){
		MF_PrintSrvConsole("No More Custom Weapon Slots!\n");
		return 0;
	}

	int iLen;
	char *szName = MF_GetAmxString(amx, params[1], 0, &iLen);
	char *szLogName = MF_GetAmxString(amx, params[3], 0, &iLen);

	strcpy(weaponData[i].name,szName);
	strcpy(weaponData[i].logname,szLogName);
	weaponData[i].ammoSlot = 1;
	weaponData[i].melee = params[2] ? true:false;

	return i;
}

static cell AMX_NATIVE_CALL custom_wpn_dmg(AMX *amx, cell *params){ // wid,att,vic,dmg,hp=0
	int weapon = params[1];
	if (  weapon < MAX_WEAPONS || weapon >= MAX_WEAPONS+MAX_CWEAPONS ||  !weaponData[weapon].ammoSlot ){ // only for custom weapons
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		MF_PrintSrvConsole("Weapon ID Is Not Valid!\n");
		return 0;
	}

	int att = params[2];
	if (att<1||att>gpGlobals->maxClients){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}

	int vic = params[3];
	if (vic<1||vic>gpGlobals->maxClients){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}
	
	int dmg = params[4];
	if ( dmg<1 ){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}
	
	int aim = params[5];
	if ( aim < 0 || aim > 7 ){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}

	CPlayer* pAtt = GET_PLAYER_POINTER_I(att);
	CPlayer* pVic = GET_PLAYER_POINTER_I(vic);

	pVic->pEdict->v.dmg_inflictor = NULL;
	pAtt->saveHit( pVic , weapon , dmg, aim );

	if ( !pAtt ) pAtt = pVic;
	int TA = 0;
	if ( (pVic->teamId == pAtt->teamId) && ( pVic != pAtt) )
		TA = 1;
	g_damage_info.exec( pAtt->index, pVic->index, dmg, weapon, aim, TA );
	
	if ( pVic->IsAlive() )
		return 1;

	pAtt->saveKill(pVic,weapon,( aim == 1 ) ? 1:0 ,TA);
	g_death_info.exec( pAtt->index, pVic->index, weapon, aim, TA );

	return 1;
}

static cell AMX_NATIVE_CALL custom_wpn_shot(AMX *amx, cell *params){ // player,wid
	int index = params[2];
	if (index<1||index>gpGlobals->maxClients){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}

	int weapon = params[1];
	if (  weapon < MAX_WEAPONS  || weapon >= MAX_WEAPONS+MAX_CWEAPONS ||  !weaponData[weapon].ammoSlot ){
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		MF_PrintSrvConsole("Weapon ID Is Not Valid!\n");
		return 0;
	}

	CPlayer* pPlayer = GET_PLAYER_POINTER_I(index);
	pPlayer->saveShot(weapon);

	return 1;
}

static cell AMX_NATIVE_CALL get_wpnname(AMX *amx, cell *params){ 
	int id = params[1];
	if (id<0 || id>=MAX_WEAPONS+MAX_CWEAPONS ){ 
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		MF_PrintSrvConsole("Weapon ID Is Not Valid!\n");
		return 0;
	}
	return MF_SetAmxString(amx,params[2],weaponData[id].name,params[3]);
}

static cell AMX_NATIVE_CALL get_wpnlogname(AMX *amx, cell *params){ 
	int id = params[1];
	if (id<0 || id>=MAX_WEAPONS+MAX_CWEAPONS ){ 
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		MF_PrintSrvConsole("Weapon ID Is Not Valid!\n");
		return 0;
	}
	return MF_SetAmxString(amx,params[2],weaponData[id].logname,params[3]);
}

static cell AMX_NATIVE_CALL is_melee(AMX *amx, cell *params){ 
	int id = params[1];
	if (id<0 || id>=MAX_WEAPONS+MAX_CWEAPONS ){ 
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		MF_PrintSrvConsole("Weapon ID Is Not Valid!\n");
		return 0;
	}
	if ( id = 29 )
		return 1;
	return weaponData[id].melee ? 1:0;
}

static cell AMX_NATIVE_CALL register_forward(AMX *amx, cell *params){ // forward 
	int iFunctionIndex;
	switch( params[1] ){
	case 0:
		if( MF_AmxFindPublic(amx, "client_damage", &iFunctionIndex) == AMX_ERR_NONE )
			g_damage_info.put( amx , iFunctionIndex );
		else
			MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
			return 0;
		break;
	case 1:
		if( MF_AmxFindPublic(amx, "client_death", &iFunctionIndex) == AMX_ERR_NONE )
			g_death_info.put( amx , iFunctionIndex );
		else
			MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
			return 0;
		break;
	default:
		MF_RaiseAmxError(amx,AMX_ERR_NATIVE);
		return 0;
	}
	return 1;
}

static cell AMX_NATIVE_CALL get_maxweapons(AMX *amx, cell *params){
	return MAX_WEAPONS+MAX_CWEAPONS;
}

static cell AMX_NATIVE_CALL get_stats_size(AMX *amx, cell *params){
	return 8;
}

AMX_NATIVE_INFO stats_Natives[] = {
	{ "get_stats",      get_stats},
	{ "get_stats2",      get_stats2},
	{ "get_statsnum",   get_statsnum},
	{ "get_user_astats",  get_user_astats },
	{ "get_user_rstats",  get_user_rstats },
	{ "get_user_lstats",  get_user_rstats }, // for backward compatibility
	{ "get_user_stats",   get_user_stats },
	{ "get_user_stats2",   get_user_stats2 },
	{ "get_user_vstats",  get_user_vstats },
	{ "get_user_wrstats",  get_user_wrstats},             // DEC-Weapon(Round) Stats
	{ "get_user_wstats",  get_user_wstats},
	{ "reset_user_wstats",  reset_user_wstats },

	// Custom Weapon Support
	{ "custom_weapon_add", register_cwpn },
	{ "custom_weapon_dmg", custom_wpn_dmg },
	{ "custom_weapon_shot", custom_wpn_shot },

	{ "xmod_get_wpnname", get_wpnname },
	{ "xmod_get_wpnlogname", get_wpnlogname },
	{ "xmod_is_melee_wpn", is_melee },
	{ "xmod_get_maxweapons", get_maxweapons },
	{ "xmod_get_stats_size", get_stats_size },

	{ "register_statsfwd",register_forward },

	///*******************
	{ NULL, NULL }
};

