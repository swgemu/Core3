mature_snorbal_male = Creature:new {
	objectName = "@mob/creature_names:mature_snorbal_male",
	socialGroup = "snorbal",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 32,
	chanceHit = 0.4,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3188,
	baseHAM = 8600,
	baseHAMmax = 10200,
	armor = 0,
	resists = {135,135,20,-1,-1,-1,-1,20,-1},
	meatType = "meat_herbivore",
	meatAmount = 545,
	hideType = "hide_leathery",
	hideAmount = 440,
	boneType = "bone_mammal",
	boneAmount = 400,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/elder_snorbal_male.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = 1.1,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"posturedownattack",""}, {"stunattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(mature_snorbal_male, "mature_snorbal_male")
