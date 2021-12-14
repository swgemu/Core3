enraged_defender = Creature:new {
	objectName = "@mob/creature_names:piket_enraged_defender",
	socialGroup = "piket",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 49,
	chanceHit = 0.47,
	damageMin = 385,
	damageMax = 480,
	baseXp = 4734,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 1,
	resists = {140,140,120,0,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 200,
	hideType = "hide_scaley",
	hideAmount = 120,
	boneType = "bone_mammal",
	boneAmount = 110,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/piket_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/piket_hue.iff",
	scale = 1.2,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"posturedownattack",""}, {"blindattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(enraged_defender, "enraged_defender")
