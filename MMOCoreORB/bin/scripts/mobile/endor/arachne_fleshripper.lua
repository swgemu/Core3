arachne_fleshripper = Creature:new {
	objectName = "@mob/creature_names:arachne_fleshripper",
	socialGroup = "arachne",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 30,
	chanceHit = 0.36,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3097,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {110,140,-1,120,120,15,120,15,-1},
	meatType = "meat_insect",
	meatAmount = 55,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 10,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/angler_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	controlDeviceTemplate = "object/intangible/pet/angler_hue.iff",
	scale = 1.05,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_spray_toxicgreen.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"strongpoison",""}, {"posturedownattack",""} },
	secondaryAttacks = { {"posturedownattack",""} }
}

CreatureTemplates:addCreatureTemplate(arachne_fleshripper, "arachne_fleshripper")
