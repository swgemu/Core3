reclusive_shear_mite = Creature:new {
	objectName = "@mob/creature_names:reclusive_shear_mite",
	socialGroup = "shear_mite",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 26,
	chanceHit = 0.35,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2637,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {130,135,-1,160,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "hide_scaley",
	hideAmount = 12,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 4,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/shear_mite_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	controlDeviceTemplate = "object/intangible/pet/shear_mite_hue.iff",
	scale = 1.1,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_small_green.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = {{"blindattack",""}},
	secondaryAttacks = {{"blindattack",""}},
}

CreatureTemplates:addCreatureTemplate(reclusive_shear_mite, "reclusive_shear_mite")
