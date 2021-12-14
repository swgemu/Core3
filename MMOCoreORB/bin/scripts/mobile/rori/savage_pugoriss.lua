savage_pugoriss = Creature:new {
	objectName = "@mob/creature_names:savage_pugoriss",
	socialGroup = "pugoriss",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 15,
	chanceHit = 0.3,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2400,
	baseHAMmax = 4000,
	armor = 0,
	resists = {0,105,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 350,
	hideType = "hide_leathery",
	hideAmount = 400,
	boneType = "bone_mammal",
	boneAmount = 350,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/pugoriss_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	controlDeviceTemplate = "object/intangible/pet/pugoriss_hue.iff",
	scale = 1.05,
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

CreatureTemplates:addCreatureTemplate(savage_pugoriss, "savage_pugoriss")
