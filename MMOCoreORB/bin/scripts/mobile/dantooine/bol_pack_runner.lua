bol_pack_runner = Creature:new {
	objectName = "@mob/creature_names:bol_pack_runner",
	socialGroup = "bol",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 26,
	chanceHit = 0.36,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2637,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {125,125,15,15,-1,-1,15,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 180,
	hideType = "hide_leathery",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/bol_pack_runner.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 0.95,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"stunattack",""}, {"dizzyattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(bol_pack_runner, "bol_pack_runner")
