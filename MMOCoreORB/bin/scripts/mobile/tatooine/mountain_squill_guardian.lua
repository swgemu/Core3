mountain_squill_guardian = Creature:new {
	objectName = "@mob/creature_names:mountain_squill_guardian",
	socialGroup = "squill",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 40,
	chanceHit = 0.42,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3915,
	baseHAM = 8900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {160,160,25,-1,25,25,25,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 3,
	hideType = "hide_leathery",
	hideAmount = 4,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0,
	ferocity = 10,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/mountain_squill.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = 1.2,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"intimidationattack",""}, {"knockdownattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(mountain_squill_guardian, "mountain_squill_guardian")
