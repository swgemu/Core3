female_mawgax = Creature:new {
	objectName = "@mob/creature_names:mawgax_female",
	socialGroup = "mawgax",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 23,
	chanceHit = 0.35,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2219,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {115,115,10,-1,10,10,-1,-1,-1},
	meatType = "meat_domesticated",
	meatAmount = 115,
	hideType = "hide_leathery",
	hideAmount = 72,
	boneType = "bone_avian",
	boneAmount = 52,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/mawgax_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"",""}, {"stunattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(female_mawgax, "female_mawgax")
