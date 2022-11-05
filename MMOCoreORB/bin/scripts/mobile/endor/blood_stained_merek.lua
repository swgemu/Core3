blood_stained_merek = Creature:new {
	objectName = "@mob/creature_names:blood_stained_merek",
	socialGroup = "merek",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 32,
	chanceHit = 0.4,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3279,
	baseHAM = 8600,
	baseHAMmax = 10500,
	armor = 0,
	resists = {-1,145,20,160,160,20,175,-1,-1},
	meatType = "meat_wild",
	meatAmount = 55,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/merek_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	controlDeviceTemplate = "object/intangible/pet/merek_hue.iff",
	scale = 0.9,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_large_green.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"knockdownattack",""} },
	secondaryAttacks = { {"knockdownattack",""} },
}

CreatureTemplates:addCreatureTemplate(blood_stained_merek, "blood_stained_merek")
