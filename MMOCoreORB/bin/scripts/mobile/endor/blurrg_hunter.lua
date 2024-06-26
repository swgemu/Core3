blurrg_hunter = Creature:new {
	objectName = "@mob/creature_names:blurrg_hunter",
	socialGroup = "blurrg",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 20,
	chanceHit = 0.32,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1609,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {115,120,5,135,135,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 50,
	hideType = "hide_leathery",
	hideAmount = 40,
	boneType = "bone_avian",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/blurrg_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	scale = 0.85,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_large_toxicgreen.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"posturedownattack",""}, {"knockdownattack",""} },
	secondaryAttacks = { {"posturedownattack",""}, {"knockdownattack",""} }
}

CreatureTemplates:addCreatureTemplate(blurrg_hunter, "blurrg_hunter")
