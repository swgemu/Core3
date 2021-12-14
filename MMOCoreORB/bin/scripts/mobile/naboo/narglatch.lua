narglatch = Creature:new {
	objectName = "@mob/creature_names:narglatch",
	socialGroup = "narglatch",
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
	resists = {125,10,10,-1,10,150,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 75,
	hideType = "hide_bristley",
	hideAmount = 45,
	boneType = "bone_mammal",
	boneAmount = 40,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/narglatch_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/narglatch_hue.iff",
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"dizzyattack",""}, {"stunattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(narglatch, "narglatch")
