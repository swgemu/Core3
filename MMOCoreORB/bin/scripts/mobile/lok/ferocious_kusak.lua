ferocious_kusak = Creature:new {
	objectName = "@mob/creature_names:ferocious_kusak",
	socialGroup = "kusak",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 21,
	chanceHit = 0.33,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2006,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {130,10,10,-1,10,10,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 21,
	hideType = "hide_bristley",
	hideAmount = 10,
	boneType = "bone_mammal",
	boneAmount = 11,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kusak_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/kusak_hue.iff",
	scale = 1.05,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"blindattack",""}, {"posturedownattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(ferocious_kusak, "ferocious_kusak")
