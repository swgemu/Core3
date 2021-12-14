riverside_sulfur_mynock = Creature:new {
	objectName = "@mob/creature_names:riverside_sulfur_mynock",
	socialGroup = "mynock",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 33,
	chanceHit = 0.4,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3370,
	baseHAM = 8600,
	baseHAMmax = 10500,
	armor = 1,
	resists = {-1,135,0,165,-1,0,165,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 60,
	hideType = "hide_leathery",
	hideAmount = 78,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/riverside_sulfur_mynock.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	controlDeviceTemplate = "object/intangible/pet/salt_mynock_hue.iff",
	scale = 1.1,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"blindattack",""}, {"mediumdisease",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(riverside_sulfur_mynock, "riverside_sulfur_mynock")
