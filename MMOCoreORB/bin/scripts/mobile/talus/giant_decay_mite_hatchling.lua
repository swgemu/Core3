giant_decay_mite_hatchling = Creature:new {
	objectName = "@mob/creature_names:giant_decay_mite_hatchling",
	socialGroup = "mite",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 7,
	chanceHit = 0.25,
	damageMin = 50,
	damageMax = 55,
	baseXp = 187,
	baseHAM = 113,
	baseHAMmax = 138,
	armor = 0,
	resists = {110,110,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 5,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/decay_mite.iff"},
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"",""}, {"milddisease",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(giant_decay_mite_hatchling, "giant_decay_mite_hatchling")
