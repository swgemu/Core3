perlek_ravager = Creature:new {
	objectName = "@mob/creature_names:perlek_ravager",
	socialGroup = "perlek",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 18,
	chanceHit = 0.32,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1426,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {5,5,5,150,150,-1,150,-1,-1},
	meatType = "meat_avian",
	meatAmount = 275,
	hideType = "hide_leathery",
	hideAmount = 115,
	boneType = "bone_avian",
	boneAmount = 190,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/perlek_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/perlek_hue.iff",
	scale = 1.15,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_small_red.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"dizzyattack",""}, {"stunattack",""} },
	secondaryAttacks = { {"dizzyattack",""}, {"stunattack",""} }
}

CreatureTemplates:addCreatureTemplate(perlek_ravager, "perlek_ravager")
