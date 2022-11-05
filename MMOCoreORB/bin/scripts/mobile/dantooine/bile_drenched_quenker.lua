bile_drenched_quenker = Creature:new {
	objectName = "@mob/creature_names:bile_drenched_quenker",
	socialGroup = "quenker",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 34,
	chanceHit = 0.41,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3370,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {30,30,30,30,-1,30,30,-1,-1},
	meatType = "meat_wild",
	meatAmount = 65,
	hideType = "hide_scaley",
	hideAmount = 35,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/bile_drenched_quenker.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/quenker_hue.iff",
	scale = 1.1,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_small_yellow.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"dizzyattack",""}, {"strongpoison",""} },
	secondaryAttacks = { {"dizzyattack",""}, {"strongpoison",""} },
}

CreatureTemplates:addCreatureTemplate(bile_drenched_quenker, "bile_drenched_quenker")
