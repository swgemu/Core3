mutant_hermit_spider = Creature:new {
	objectName = "",
	customName = "a mutant hermit spider",
	socialGroup = "spider",
	mobType = MOB_CARNIVORE,
	faction = "",
	level = 7,
	chanceHit = 0.3,
	damageMin = 75,
	damageMax = 95,
	baseXp = 247,
	baseHAM = 300,
	baseHAMmax = 360,
	armor = 0,
	resists = {0,0,110,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 70,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/hermit_spider_hue.iff"},
	scale = 1.5,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"intimidationattack",""}, {"mildpoison",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(mutant_hermit_spider, "mutant_hermit_spider")
