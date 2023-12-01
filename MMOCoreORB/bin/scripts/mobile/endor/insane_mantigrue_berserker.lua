insane_mantigrue_berserker = Creature:new {
	objectName = "@mob/creature_names:mantigrue_insane_berserker",
	socialGroup = "mantigrue",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 50,
	chanceHit = 0.43,
	damageMin = 400,
	damageMax = 510,
	baseXp = 4916,
	baseHAM = 9200,
	baseHAMmax = 11200,
	armor = 1,
	resists = {150,150,200,150,-1,120,120,200,-1},
	meatType = "meat_carnivore",
	meatAmount = 85,
	hideType = "hide_wooly",
	hideAmount = 75,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 10,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/mantigrue_night_stalker.iff"},
	controlDeviceTemplate = "object/intangible/pet/perlek_hue.iff",
	scale = 1.25,
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

CreatureTemplates:addCreatureTemplate(insane_mantigrue_berserker, "insane_mantigrue_berserker")
