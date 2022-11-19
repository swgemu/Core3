reclusive_cavern_spider = Creature:new {
	objectName = "@mob/creature_names:cave_gaping_spider_recluse",
	socialGroup = "spider_nightsister",
	faction = "spider_nightsister",
	mobType = MOB_CARNIVORE,
	level = 46,
	chanceHit = 0.46,
	damageMin = 510,
	damageMax = 730,
	baseXp = 4552,
	baseHAM = 11000,
	baseHAMmax = 12000,
	armor = 1,
	resists = {140,140,160,125,-1,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 41,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 8,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider_recluse.iff"},
	scale = 1.25,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_spray_red.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"creatureareaattack",""}, {"strongpoison",""} },
	secondaryAttacks = { {"creatureareaattack",""} }
}

CreatureTemplates:addCreatureTemplate(reclusive_cavern_spider, "reclusive_cavern_spider")
