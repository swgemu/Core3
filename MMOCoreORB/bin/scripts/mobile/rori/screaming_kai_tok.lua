screaming_kai_tok = Creature:new {
	objectName = "@mob/creature_names:screaming_kai_tok",
	socialGroup = "kai_tok",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 21,
	chanceHit = 0.32,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1803,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {120,110,135,145,145,5,5,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 25,
	hideType = "hide_leathery",
	hideAmount = 41,
	boneType = "bone_avian",
	boneAmount = 46,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 5,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kai_tok_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	controlDeviceTemplate = "object/intangible/pet/kai_tok_hue.iff",
	scale = 1.1,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_spray_red.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"dizzyattack",""} },
	secondaryAttacks = { {"dizzyattack",""} }
}

CreatureTemplates:addCreatureTemplate(screaming_kai_tok, "screaming_kai_tok")
