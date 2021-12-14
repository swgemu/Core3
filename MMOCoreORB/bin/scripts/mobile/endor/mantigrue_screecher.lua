mantigrue_screecher = Creature:new {
	objectName = "@mob/creature_names:mantigrue_screecher",
	socialGroup = "mantigrue",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 55,
	chanceHit = 0.55,
	damageMin = 420,
	damageMax = 550,
	baseXp = 5281,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {135,135,10,10,10,-1,10,10,-1},
	meatType = "meat_carnivore",
	meatAmount = 85,
	hideType = "hide_wooly",
	hideAmount = 65,
	boneType = "bone_avian",
	boneAmount = 45,
	milk = 0,
	tamingChance = 0.01,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/mantigrue_night_stalker.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	controlDeviceTemplate = "object/intangible/pet/perlek_hue.iff",
	scale = 1.2,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"intimidationattack",""}, {"creatureareadisease",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(mantigrue_screecher, "mantigrue_screecher")
