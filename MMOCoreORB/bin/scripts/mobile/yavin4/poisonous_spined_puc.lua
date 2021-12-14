poisonous_spined_puc = Creature:new {
	objectName = "@mob/creature_names:spined_puc_poison",
	socialGroup = "spined_puc",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 19,
	chanceHit = 0.33,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1426,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {110,10,10,-1,-1,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 7,
	hideType = "hide_leathery",
	hideAmount = 7,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/spined_puc_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/spined_puc_hue.iff",
	scale = 1.2,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"strongpoison",""}, {"stunattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(poisonous_spined_puc, "poisonous_spined_puc")
