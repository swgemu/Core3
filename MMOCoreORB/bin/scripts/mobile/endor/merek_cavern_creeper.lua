merek_cavern_creeper = Creature:new {
	objectName = "@mob/creature_names:merek_cavern_creeper",
	socialGroup = "merek",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 40,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 3915,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {140,30,30,30,-1,30,30,30,-1},
	meatType = "meat_wild",
	meatAmount = 64,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/merek_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/merek_hue.iff",
	scale = 0.95,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_large_yellow.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"blindattack",""}, {"intimidationattack",""} },
	secondaryAttacks = { {"blindattack",""}, {"intimidationattack",""} },
}

CreatureTemplates:addCreatureTemplate(merek_cavern_creeper, "merek_cavern_creeper")
