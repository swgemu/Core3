dune_bantha = Creature:new {
	objectName = "@mob/creature_names:dune_bantha",
	socialGroup = "bantha",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 17,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 960,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {5,5,5,140,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 375,
	hideType = "hide_wooly",
	hideAmount = 275,
	boneType = "bone_mammal",
	boneAmount = 175,
	milkType = "milk_wild",
	milk = 225,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/bantha_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	controlDeviceTemplate = "object/intangible/pet/bantha_hue.iff",
	scale = 1.15,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"",""}, {"stunattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(dune_bantha, "dune_bantha")
