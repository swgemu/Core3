vehement_warrior = Creature:new {
	objectName = "@mob/creature_names:durni_vehement_warrior",
	socialGroup = "durni",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 9,
	chanceHit = 0.28,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 625,
	baseHAMmax = 825,
	armor = 0,
	resists = {105,105,0,0,0,0,0,110,-1},
	meatType = "meat_herbivore",
	meatAmount = 5,
	hideType = "hide_wooly",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 5,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/durni.iff"},
	controlDeviceTemplate = "object/intangible/pet/durni_hue.iff",
	scale = 1.25,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"intimidationattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(vehement_warrior, "vehement_warrior")
