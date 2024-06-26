mutant_bark_mite_soldier = Creature:new {
	objectName = "@mob/creature_names:mutant_bark_mite_soldier",
	socialGroup = "mite",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 24,
	chanceHit = 0.33,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2543,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {130,130,-1,120,120,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 25,
	hideType = "hide_scaley",
	hideAmount = 20,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 2.5,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_large_toxicgreen.iff",
	secondaryWeapon = "object/weapon/ranged/creature/creature_spit_large_toxicgreen.iff",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"strongpoison",""} },
	secondaryAttacks = { {"strongpoison",""} }
}

CreatureTemplates:addCreatureTemplate(mutant_bark_mite_soldier, "mutant_bark_mite_soldier")
