blurrg = Creature:new {
	objectName = "@mob/creature_names:blurrg",
	socialGroup = "blurrg",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 50,
	chanceHit = 0.5,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4825,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 1,
	resists = {120,120,5,140,180,180,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 85,
	boneType = "bone_avian",
	boneAmount = 75,
	milk = 0,
	tamingChance = 0.1,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/blurrg_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	controlDeviceTemplate = "object/intangible/pet/blurrg_hue.iff",
	scale = 1.2,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_large_yellow.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"stunattack",""}, {"blindattack",""} },
	secondaryAttacks = { {"stunattack",""}, {"blindattack",""} },
}

CreatureTemplates:addCreatureTemplate(blurrg, "blurrg")
