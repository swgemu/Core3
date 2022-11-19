blister_rot_mite_queen = Creature:new {
	objectName = "@mob/creature_names:blister_rot_queen",
	socialGroup = "mite",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 15,
	chanceHit = 0.3,
	damageMin = 160,
	damageMax = 170,
	baseXp = 960,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {0,0,0,0,110,0,110,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
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

	templates = {"object/mobile/blister_rot_queen.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 1.25,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_spray_toxicgreen.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"mediumdisease",""}, {"stunattack",""} },
	secondaryAttacks = { {"stunattack",""} }
}

CreatureTemplates:addCreatureTemplate(blister_rot_mite_queen, "blister_rot_mite_queen")
