giant_fynock = Creature:new {
	objectName = "@mob/creature_names:giant_fynock",
	socialGroup = "fynock",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 42,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4188,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {30,30,30,30,30,30,30,30,-1},
	meatType = "meat_avian",
	meatAmount = 70,
	hideType = "hide_leathery",
	hideAmount = 50,
	boneType = "bone_avian",
	boneAmount = 55,
	milk = 0,
	tamingChance = 0,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/fynock_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 4,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_large_yellow.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"intimidationattack",""}, {"creatureareaknockdown",""} },
	secondaryAttacks = { {"intimidationattack",""}, {"creatureareaknockdown",""} },
}

CreatureTemplates:addCreatureTemplate(giant_fynock, "giant_fynock")
