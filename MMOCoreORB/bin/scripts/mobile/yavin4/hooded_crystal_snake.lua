hooded_crystal_snake = Creature:new {
	objectName = "@mob/creature_names:crystal_snake_hooded",
	socialGroup = "snake",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 26,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2637,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {120,120,15,15,-1,-1,160,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_scaley",
	hideAmount = 2,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/crystal_snake.iff"},
	controlDeviceTemplate = "object/intangible/pet/crystal_snake.iff",
	scale = 1.2,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_small_toxicgreen.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"mediumpoison",""}, {"stunattack",""} },
	secondaryAttacks = { {"mediumpoison",""}, {"stunattack",""} }
}

CreatureTemplates:addCreatureTemplate(hooded_crystal_snake, "hooded_crystal_snake")
