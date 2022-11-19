rhoa_kwi_guardian = Creature:new {
	objectName = "@mob/creature_names:rhoa_kwi_guardian",
	socialGroup = "kwi",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 45,
	chanceHit = 0.44,
	damageMin = 320,
	damageMax = 350,
	baseXp = 4461,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {140,165,30,180,30,30,115,30,-1},
	meatType = "meat_carnivore",
	meatAmount = 120,
	hideType = "hide_leathery",
	hideAmount = 86,
	boneType = "bone_mammal",
	boneAmount = 76,
	milk = 0,
	tamingChance = 0.15,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kwi_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	controlDeviceTemplate = "object/intangible/pet/kwi_hue.iff",
	scale = 1.25,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_spray_green.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"posturedownattack",""}, {"dizzyattack",""} },
	secondaryAttacks = { {"posturedownattack",""}, {"dizzyattack",""} }
}

CreatureTemplates:addCreatureTemplate(rhoa_kwi_guardian, "rhoa_kwi_guardian")
