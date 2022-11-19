giant_decay_mite_sentry = Creature:new {
	objectName = "@mob/creature_names:giant_decay_mite_sentry",
	socialGroup = "mite",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 18,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 3200,
	baseHAMmax = 3200,
	armor = 0,
	resists = {120,120,-1,5,5,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "hide_scaley",
	hideAmount = 14,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/decay_mite.iff"},
	scale = 1.8,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_spray_toxicgreen.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"knockdownattack",""}, {"mediumdisease",""} },
	secondaryAttacks = { {"knockdownattack",""} }
}

CreatureTemplates:addCreatureTemplate(giant_decay_mite_sentry, "giant_decay_mite_sentry")
