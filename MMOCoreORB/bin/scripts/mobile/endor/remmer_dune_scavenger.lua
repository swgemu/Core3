remmer_dune_scavenger = Creature:new {
	objectName = "@mob/creature_names:remmer_dune_scavenger",
	socialGroup = "remmer",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 20,
	chanceHit = 0.33,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1609,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {115,5,125,135,-1,5,5,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 30,
	hideType = "hide_bristley",
	hideAmount = 15,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 5,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/remmer_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 0.9,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_spray_red.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"posturedownattack",""}, {"stunattack",""} },
	secondaryAttacks = { {"posturedownattack",""}, {"stunattack",""} },
}

CreatureTemplates:addCreatureTemplate(remmer_dune_scavenger, "remmer_dune_scavenger")
