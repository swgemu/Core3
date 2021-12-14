graul_mauler = Creature:new {
	objectName = "@mob/creature_names:graul_mauler",
	socialGroup = "graul",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 35,
	chanceHit = 0.41,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3551,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {145,20,160,160,160,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 875,
	boneType = "bone_mammal",
	boneAmount = 775,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 10,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/graul_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	controlDeviceTemplate = "object/intangible/pet/graul_hue.iff",
	scale = 1.05,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"posturedownattack",""}, {"intimidationattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(graul_mauler, "graul_mauler")
