poisonous_krevol_queen = Creature:new {
	objectName = "@mob/creature_names:poisonous_krevol_queen",
	socialGroup = "krevol",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 15,
	chanceHit = 0.3,
	damageMin = 170,
	damageMax = 180,
	baseXp = 960,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {125,0,0,-1,120,0,120,-1,-1},
	meatType = "meat_insect",
	meatAmount = 12,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/poisonous_krevol_queen.iff"},
	scale = 1.15,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_spray_toxicgreen.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"blindattack",""}, {"mediumpoison",""} },
	secondaryAttacks = { {"blindattack",""} }
}

CreatureTemplates:addCreatureTemplate(poisonous_krevol_queen, "poisonous_krevol_queen")
