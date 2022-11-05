savage_quenker = Creature:new {
	objectName = "@mob/creature_names:savage_quenker",
	socialGroup = "quenker",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 28,
	chanceHit = 0.36,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2822,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {135,135,15,15,-1,15,15,-1,-1},
	meatType = "meat_wild",
	meatAmount = 35,
	hideType = "hide_scaley",
	hideAmount = 35,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/quenker_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	controlDeviceTemplate = "object/intangible/pet/quenker_hue.iff",
	scale = 1.05,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_small_yellow.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"intimidationattack",""}, {"stunattack",""} },
	secondaryAttacks = { {"intimidationattack",""}, {"stunattack",""} },
}

CreatureTemplates:addCreatureTemplate(savage_quenker, "savage_quenker")
