runty_pharple = Creature:new {
	objectName = "@mob/creature_names:runty_pharple",
	socialGroup = "pharple",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 3,
	chanceHit = 0.23,
	damageMin = 35,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 90,
	baseHAMmax = 110,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 15,
	hideType = "hide_bristley",
	hideAmount = 7,
	boneType = "bone_avian",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/runty_pharple.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 0.9,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = {},
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(runty_pharple, "runty_pharple")
