giga_flite_rasp = Creature:new {
	objectName = "@mob/creature_names:giga_flite_rasp",
	socialGroup = "rasp",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 11,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 430,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {0,0,0,0,0,115,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 20,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 6,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/flite_rasp_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = 1.2,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"",""}, {"posturedownattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(giga_flite_rasp, "giga_flite_rasp")
