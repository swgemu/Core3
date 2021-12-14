female_narglatch = Creature:new {
	objectName = "@mob/creature_names:narglatch_female",
	socialGroup = "narglatch",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 23,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2443,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {125,10,10,10,-1,-1,10,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/narglatch_female.iff"},
	controlDeviceTemplate = "object/intangible/pet/narglatch_hue.iff",
	scale = 1.05,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"intimidationattack",""}, {"stunattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(female_narglatch, "female_narglatch")
