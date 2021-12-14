female_mamien = Creature:new {
	objectName = "@mob/creature_names:mamien_female",
	socialGroup = "mamien",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 18,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1257,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {120,125,5,5,-1,5,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 45,
	hideType = "hide_wooly",
	hideAmount = 20,
	boneType = "bone_mammal",
	boneAmount = 20,
	milkType = "milk_wild",
	milk = 20,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/mamien_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = 0.95,
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

CreatureTemplates:addCreatureTemplate(female_mamien, "female_mamien")
