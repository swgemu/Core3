veneral_devourer = Creature:new {
	objectName = "@mob/creature_names:pugoriss_venerable_devourer",
	socialGroup = "pugoriss",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 20,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1609,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {120,120,10,125,135,10,10,10,-1},
	meatType = "meat_carnivore",
	meatAmount = 35,
	hideType = "hide_leathery",
	hideAmount = 40,
	boneType = "bone_mammal",
	boneAmount = 45,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/pugoriss.iff"},
	controlDeviceTemplate = "object/intangible/pet/pugoriss_hue.iff",
	scale = 1.25,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"intimidationattack",""}, {"blindattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(veneral_devourer, "veneral_devourer")
