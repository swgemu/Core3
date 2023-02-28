cavern_spider_hunter = Creature:new {
	objectName = "@mob/creature_names:cave_gaping_spider_hunter",
	socialGroup = "spider_nightsister",
	faction = "spider_nightsister",
	mobType = MOB_CARNIVORE,
	level = 46,
	chanceHit = 0.46,
	damageMin = 390,
	damageMax = 490,
	baseXp = 4552,
	baseHAM = 9500,
	baseHAMmax = 11600,
	armor = 1,
	resists = {140,140,160,115,-1,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 35,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	scale = 1.15,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_spray_green.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"stunattack",""}, {"mediumpoison",""} },
	secondaryAttacks = { {"stunattack",""} }
}

CreatureTemplates:addCreatureTemplate(cavern_spider_hunter, "cavern_spider_hunter")
