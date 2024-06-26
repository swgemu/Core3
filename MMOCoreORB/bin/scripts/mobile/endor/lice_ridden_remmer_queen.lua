lice_ridden_remmer_queen = Creature:new {
	objectName = "@mob/creature_names:lice_ridden_remmer_queen",
	socialGroup = "remmer",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 37,
	chanceHit = 0.41,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3642,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {155,135,160,30,30,30,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 85,
	hideType = "hide_bristley",
	hideAmount = 65,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/lice_ridden_remmer_queen.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = 1.2,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_small_toxicgreen.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"knockdownattack",""}, {"mediumdisease",""} },
	secondaryAttacks = { {"knockdownattack",""}, {"mediumdisease",""} }
}

CreatureTemplates:addCreatureTemplate(lice_ridden_remmer_queen, "lice_ridden_remmer_queen")
