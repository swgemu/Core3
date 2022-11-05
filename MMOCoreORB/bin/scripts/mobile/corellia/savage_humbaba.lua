savage_humbaba = Creature:new {
	objectName = "@mob/creature_names:savage_humbaba",
	socialGroup = "self",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 24,
	chanceHit = 0.35,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2443,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {115,135,10,-1,-1,-1,-1,-1,-1},
	meatType = "meat_domesticated",
	meatAmount = 265,
	hideType = "hide_leathery",
	hideAmount = 168,
	boneType = "bone_mammal",
	boneAmount = 118,
	milkType = "milk_wild",
	milk = 130,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/falumpaset_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	controlDeviceTemplate = "object/intangible/pet/falumpaset_hue.iff",
	scale = 2.0,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_small_green.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"stunattack",""} },
	secondaryAttacks = { {"stunattack",""} },
}

CreatureTemplates:addCreatureTemplate(savage_humbaba, "savage_humbaba")
