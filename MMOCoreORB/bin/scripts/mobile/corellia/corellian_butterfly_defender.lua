corellian_butterfly_defender = Creature:new {
	objectName = "@mob/creature_names:corellian_butterfly_defender",
	socialGroup = "butterfly",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 18,
	chanceHit = 0.32,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1257,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {5,115,-1,-1,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 16,
	hideType = "hide_scaley",
	hideAmount = 16,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/corellian_butterfly_defender.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/corellian_butterfly_hue.iff",
	scale = 1.2,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_small_toxicgreen.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"intimidationattack",""} },
	secondaryAttacks = { {"intimidationattack",""} }
}

CreatureTemplates:addCreatureTemplate(corellian_butterfly_defender, "corellian_butterfly_defender")
