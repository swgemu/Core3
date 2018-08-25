includeAiFile("templates/example.lua")
includeAiFile("templates/cantinacrackdown.lua")
includeAiFile("templates/stationary.lua")
includeAiFile("templates/stationarynoleash.lua")
includeAiFile("templates/follow.lua")
includeAiFile("templates/wait.lua")
includeAiFile("templates/idlewander.lua")
includeAiFile("templates/idlewait.lua")
includeAiFile("templates/idlepet.lua")
includeAiFile("templates/gettargetreactive.lua")
includeAiFile("templates/manualescort.lua")
includeAiFile("templates/selectattacksimple.lua")
includeAiFile("templates/combatmovesimple.lua")
includeAiFile("templates/gettargetpet.lua")
includeAiFile("templates/selectattackpet.lua")
includeAiFile("templates/combatmovepet.lua")
includeAiFile("templates/villageraider.lua")
includeAiFile("templates/enclavesentinel.lua")
includeAiFile("templates/deathwatchdefender.lua")

getTarget = {
	{CREATURE_PET, "gettargetpetc"},
	{DROID_PET, "gettargetpetd"},
	{FACTION_PET, "gettargetpetf"},
	{NONE, "gettargetreactive"},
}

selectAttack = {
	{CREATURE_PET, "selectattackpetc"},
	{DROID_PET, "selectattackpetd"},
	{FACTION_PET, "selectattackpetf"},
	{NONE, "selectattacksimple"},
}

combatMove = {
	{CREATURE_PET, "combatmovepetc"},
	{DROID_PET, "combatmovepetd"},
	{FACTION_PET, "combatmovepetf"},
	{NONE, "combatmovesimple"},
}

idle = {
	{CREATURE_PET, "idlepetc"},
	{DROID_PET, "idlepetd"},
	{FACTION_PET, "idlepetf"},
	{STATIC + WANDER, "idlewanderstatic"},
	{STATIC, "idlewait"},
	{PACK, "idlewanderpack"},
	{NONE, "idlewander"},
}

addAiBehavior("Composite")
addAiBehavior("Wait")
addAiBehavior("Wait10")
addAiBehavior("Move")
addAiBehavior("Walk")
addAiBehavior("CombatMove")
addAiBehavior("GeneratePatrol")
addAiBehavior("GetTarget")
addAiBehavior("SelectAttack")
addAiBehavior("SelectWeapon")

addAiBehavior("CompositeDefault")
addAiBehavior("WaitDefault")
addAiBehavior("Wait10Default")
addAiBehavior("MoveDefault")
addAiBehavior("WalkDefault")
addAiBehavior("GeneratePatrolDefault")

addAiBehavior("CompositePack")
addAiBehavior("WaitPack")
addAiBehavior("Wait10Pack")
addAiBehavior("MovePack")
addAiBehavior("WalkPack")
addAiBehavior("GeneratePatrolPack")

addAiBehavior("CompositeCreaturePet")
addAiBehavior("WaitCreaturePet")
addAiBehavior("Wait10CreaturePet")
addAiBehavior("MoveCreaturePet")
addAiBehavior("WalkCreaturePet")
addAiBehavior("CombatMoveCreaturePet")
addAiBehavior("GetTargetCreaturePet")
addAiBehavior("SelectAttackCreaturePet")
addAiBehavior("SelectWeaponCreaturePet")
addAiBehavior("MoveEscort")

addAiBehavior("CompositeDroidPet")
addAiBehavior("WaitDroidPet")
addAiBehavior("Wait10DroidPet")
addAiBehavior("MoveDroidPet")
addAiBehavior("WalkDroidPet")
addAiBehavior("CombatMoveDroidPet")
addAiBehavior("GetTargetDroidPet")
addAiBehavior("SelectAttackDroidPet")
addAiBehavior("SelectWeaponDroidPet")

addAiBehavior("CompositeFactionPet")
addAiBehavior("WaitFactionPet")
addAiBehavior("Wait10FactionPet")
addAiBehavior("MoveFactionPet")
addAiBehavior("WalkFactionPet")
addAiBehavior("CombatMoveFactionPet")
addAiBehavior("GetTargetFactionPet")
addAiBehavior("SelectAttackFactionPet")
addAiBehavior("SelectWeaponFactionPet")

addAiBehavior("CompositeVillageRaider")
addAiBehavior("MoveVillageRaider")
addAiBehavior("CombatMoveVillageRaider")
addAiBehavior("GetTargetVillageRaider")
addAiBehavior("SelectAttackVillageRaider")
addAiBehavior("SelectWeaponVillageRaider")
addAiBehavior("Wait10VillageRaider")
addAiBehavior("GeneratePatrolVillageRaider")

addAiBehavior("CompositeEnclaveSentinel")
addAiBehavior("MoveEnclaveSentinel")
addAiBehavior("CombatMoveEnclaveSentinel")
addAiBehavior("WaitEnclaveSentinel")
addAiBehavior("SelectAttackEnclaveSentinel")
addAiBehavior("SelectWeaponEnclaveSentinel")
addAiBehavior("GetTargetEnclaveSentinel")

addAiBehavior("CompositeDeathWatchDefender")
addAiBehavior("MoveDeathWatchDefender")
addAiBehavior("CombatMoveDeathWatchDefender")
addAiBehavior("WaitDeathWatchDefender")
addAiBehavior("SelectAttackDeathWatchDefender")
addAiBehavior("SelectWeaponDeathWatchDefender")
addAiBehavior("GetTargetDeathWatchDefender")