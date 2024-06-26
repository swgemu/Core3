nightspider_poison_spitter = Creature:new {
	objectName = "@mob/creature_names:nightspider_poison_spitter",
	socialGroup = "spider",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 11,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 430,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {0,0,0,0,0,0,115,-1,-1},
	meatType = "meat_insect",
	meatAmount = 7,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/nightspider_poison_spitter.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 0.6,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_small_toxicgreen.iff",
	secondaryWeapon = "object/weapon/ranged/creature/creature_spit_small_toxicgreen.iff",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"stunattack",""}, {"mildpoison",""} },
	secondaryAttacks = { {"stunattack",""}, {"mildpoison",""} }
}

CreatureTemplates:addCreatureTemplate(nightspider_poison_spitter, "nightspider_poison_spitter")
