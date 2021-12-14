mature_reptilian_flier = Creature:new {
	objectName = "@mob/creature_names:mature_reptilian_flier",
	socialGroup = "reptilian_flier",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 20,
	chanceHit = 0.32,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1609,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {5,110,5,135,135,-1,5,-1,-1},
	meatType = "meat_avian",
	meatAmount = 130,
	hideType = "hide_leathery",
	hideAmount = 85,
	boneType = "bone_avian",
	boneAmount = 80,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/reptilian_flier_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	controlDeviceTemplate = "object/intangible/pet/pet_control.iff",
	scale = 1.05,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"",""}, {"blindattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(mature_reptilian_flier, "mature_reptilian_flier")
