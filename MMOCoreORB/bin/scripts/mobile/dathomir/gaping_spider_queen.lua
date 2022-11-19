gaping_spider_queen = Creature:new {
	objectName = "@mob/creature_names:gaping_spider_queen",
	socialGroup = "spider",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 47,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4643,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {165,165,140,125,30,-1,30,30,-1},
	meatType = "meat_insect",
	meatAmount = 12,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider_queen.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/gaping_spider_hue.iff",
	scale = 1.15,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_spray_toxicgreen.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"knockdownattack",""}, {"mediumpoison",""} },
	secondaryAttacks = { {"knockdownattack",""} }
}

CreatureTemplates:addCreatureTemplate(gaping_spider_queen, "gaping_spider_queen")
