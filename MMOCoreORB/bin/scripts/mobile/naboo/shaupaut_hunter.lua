shaupaut_hunter = Creature:new {
	objectName = "@mob/creature_names:shaupaut_hunter",
	socialGroup = "shaupaut",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 22,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2006,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {120,120,10,-1,10,-1,10,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 10,
	hideType = "hide_bristley",
	hideAmount = 6,
	boneType = "bone_mammal",
	boneAmount = 6,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/shaupaut_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	controlDeviceTemplate = "object/intangible/pet/shaupaut_hue.iff",
	scale = 1.2,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"blindattack",""}, {"stunattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(shaupaut_hunter, "shaupaut_hunter")
