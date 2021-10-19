nitra_vendallan_imp2 = Creature:new {
	objectName = "",
	socialGroup = "imperial",
	faction = "imperial",
	mobType = MOB_NPC,
	level = 30,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2914,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {0,45,0,-1,40,-1,40,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED + CONVERSABLE,	
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_weaponsmith_trainer_01.iff",
		"object/mobile/dressed_weaponsmith_trainer_02.iff",
		"object/mobile/dressed_weaponsmith_trainer_03.iff"},
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = brawlermaster,
	secondaryAttacks = { },
	conversationTemplate = "nitra_vendallan_mission_target_convotemplate",	
}

CreatureTemplates:addCreatureTemplate(nitra_vendallan_imp2, "nitra_vendallan_imp2")
