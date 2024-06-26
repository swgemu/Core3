giant_cavern_spider_recluse = Creature:new {
	objectName = "@mob/creature_names:cave_gaping_spider_recluse_giant",
	socialGroup = "spider_nightsister",
	faction = "spider_nightsister",
	mobType = MOB_CARNIVORE,
	level = 116,
	chanceHit = 3.1,
	damageMin = 775,
	damageMax = 1260,
	baseXp = 11015,
	baseHAM = 33500,
	baseHAMmax = 33500,
	armor = 0,
	resists = {160,160,160,0,0,0,0,0,-1},
	meatType = "meat_insect",
	meatAmount = 80,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider_recluse.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = 2.0,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"creatureareacombo",""}, {"strongpoison",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(giant_cavern_spider_recluse, "giant_cavern_spider_recluse")
