domestic_bageraset = Creature:new {
	objectName = "@mob/creature_names:domestic_bageraset",
	socialGroup = "self",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 8,
	chanceHit = 0.27,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_domesticated",
	meatAmount = 240,
	hideType = "hide_leathery",
	hideAmount = 145,
	boneType = "bone_mammal",
	boneAmount = 104,
	milkType = "milk_domesticated",
	milk = 120,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/bageraset_hue.iff"},
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"stunattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(domestic_bageraset, "domestic_bageraset")
