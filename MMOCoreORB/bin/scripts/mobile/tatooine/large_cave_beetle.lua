large_cave_beetle = Creature:new {
	objectName = "@mob/creature_names:large_cave_beetle",
	socialGroup = "beetle",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 23,
	chanceHit = 0.35,
	damageMin = 180,
	damageMax = 190,
	baseXp = 2443,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {150,10,-1,-1,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "hide_scaley",
	hideAmount = 14,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 4,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_sand_beetle.iff"},
	controlDeviceTemplate = "object/intangible/pet/rock_mite_hue.iff",
	scale = 1.6,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_small_toxicgreen.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"posturedownattack",""} },
	secondaryAttacks = { {"posturedownattack",""} }
}

CreatureTemplates:addCreatureTemplate(large_cave_beetle, "large_cave_beetle")
