gaping_spider_recluse_queen = Creature:new {
	objectName = "@mob/creature_names:gaping_spider_recluse_queen",
	socialGroup = "spider",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 68,
	chanceHit = 0.65,
	damageMin = 510,
	damageMax = 730,
	baseXp = 6563,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {145,165,145,190,-1,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 11,
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
	scale = 1.2,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_spray_red.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"creatureareapoison",""}, {"strongpoison",""} },
	secondaryAttacks = {  {"creatureareapoison",""} }
}

CreatureTemplates:addCreatureTemplate(gaping_spider_recluse_queen, "gaping_spider_recluse_queen")
