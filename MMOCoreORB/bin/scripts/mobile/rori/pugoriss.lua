pugoriss = Creature:new {
	objectName = "@mob/creature_names:pugoriss",
	socialGroup = "pugoriss",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 14,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 609,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {110,110,0,0,115,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 375,
	hideType = "hide_leathery",
	hideAmount = 425,
	boneType = "bone_mammal",
	boneAmount = 375,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/pugoriss_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	controlDeviceTemplate = "object/intangible/pet/pugoriss_hue.iff",
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"intimidationattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(pugoriss, "pugoriss")
