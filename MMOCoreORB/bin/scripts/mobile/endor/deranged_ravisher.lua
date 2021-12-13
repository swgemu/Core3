deranged_ravisher = Creature:new {
	objectName = "@mob/creature_names:squill_deranged_ravisher",
	socialGroup = "squill",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 35,
	chanceHit = 0.39,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3460,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {140,140,15,-1,15,15,15,15,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/squill_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/squill_hue.iff",
	scale = 1.35,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"knockdownattack",""}, {"mediumdisease",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(deranged_ravisher, "deranged_ravisher")
