langlatch_marauder = Creature:new {
	objectName = "@mob/creature_names:langlatch_marauder",
	socialGroup = "langlatch",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 17,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {5,115,5,5,5,5,5,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 12,
	hideType = "hide_wooly",
	hideAmount = 11,
	boneType = "bone_mammal",
	boneAmount = 11,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/langlatch_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	controlDeviceTemplate = "object/intangible/pet/langlatch_hue.iff",
	scale = 1.1,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"blindattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(langlatch_marauder, "langlatch_marauder")
