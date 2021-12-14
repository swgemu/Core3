grizzled_dewback = Creature:new {
	objectName = "@mob/creature_names:grizzled_dewback",
	socialGroup = "dewback",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 27,
	chanceHit = 0.35,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2730,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {135,120,10,140,-1,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 365,
	hideType = "hide_leathery",
	hideAmount = 285,
	boneType = "bone_mammal",
	boneAmount = 210,
	milk = 0,
	tamingChance = 0,
	ferocity = 6,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/dewback_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 1.15,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"knockdownattack",""}, {"dizzyattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(grizzled_dewback, "grizzled_dewback")
