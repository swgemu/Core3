cowardly_gurreck = Creature:new {
	objectName = "@mob/creature_names:cowardly_gurreck",
	socialGroup = "gurreck",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 15,
	chanceHit = 0.31,
	damageMin = 150,
	damageMax = 160,
	baseXp = 831,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {110,110,5,-1,-1,5,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 55,
	hideType = "hide_wooly",
	hideAmount = 20,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/gurreck_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/gurreck_hue.iff",
	scale = 0.85,
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

CreatureTemplates:addCreatureTemplate(cowardly_gurreck, "cowardly_gurreck")
