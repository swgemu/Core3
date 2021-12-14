quenker_ravager = Creature:new {
	objectName = "@mob/creature_names:quenker_ravager",
	socialGroup = "quenker",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 38,
	chanceHit = 0.43,
	damageMin = 365,
	damageMax = 440,
	baseXp = 3824,
	baseHAM = 9100,
	baseHAMmax = 11100,
	armor = 0,
	resists = {25,25,25,25,-1,-1,25,25,-1},
	meatType = "meat_wild",
	meatAmount = 35,
	hideType = "hide_scaley",
	hideAmount = 35,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/quenker_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 1.2,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"dizzyattack",""}, {"creatureareapoison",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(quenker_ravager, "quenker_ravager")
