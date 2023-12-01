giant_cave_veermok = Creature:new {
	objectName = "@mob/creature_names:veermok_giant_cave",
	socialGroup = "veermok",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 26,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2730,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {150,150,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 290,
	hideType = "hide_bristley",
	hideAmount = 250,
	boneType = "bone_mammal",
	boneAmount = 160,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_veermok.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 3.0,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"",""}, {"stunattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(giant_cave_veermok, "giant_cave_veermok")
