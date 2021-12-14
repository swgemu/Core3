enraged_tybis = Creature:new {
	objectName = "@mob/creature_names:enraged_tybis",
	socialGroup = "tybis",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 26,
	chanceHit = 0.360000,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2637,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 220,
	hideType = "hide_bristley",
	hideAmount = 160,
	boneType = "bone_mammal",
	boneAmount = 105,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/tybis_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = 1.15,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = {},
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(enraged_tybis, "enraged_tybis")
