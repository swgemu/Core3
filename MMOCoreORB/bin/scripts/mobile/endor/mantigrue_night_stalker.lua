mantigrue_night_stalker = Creature:new {
	objectName = "@mob/creature_names:mantigrue_night_stalker",
	socialGroup = "mantigrue",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 28,
	chanceHit = 0.36,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2914,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {130,140,15,-1,-1,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 85,
	hideType = "hide_wooly",
	hideAmount = 65,
	boneType = "bone_avian",
	boneAmount = 45,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 2,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/mantigrue_night_stalker.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	controlDeviceTemplate = "object/intangible/pet/perlek_hue.iff",
	scale = 0.9,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_large_green.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"posturedownattack",""} },
	secondaryAttacks = { {"posturedownattack",""} },
}

CreatureTemplates:addCreatureTemplate(mantigrue_night_stalker, "mantigrue_night_stalker")
