shear_mite_queen = Creature:new {
	objectName = "@mob/creature_names:shear_mite_queen",
	socialGroup = "shear_mite",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 39,
	chanceHit = 0.43,
	damageMin = 340,
	damageMax = 390,
	baseXp = 3824,
	baseHAM = 9000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {130,145,-1,160,-1,160,160,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "hide_scaley",
	hideAmount = 12,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 4,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/shear_mite_queen.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 1.2,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_small_red.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"dizzyattack",""}, {"strongpoison",""} },
	secondaryAttacks = { {"dizzyattack",""}, {"strongpoison",""} },
}

CreatureTemplates:addCreatureTemplate(shear_mite_queen, "shear_mite_queen")
