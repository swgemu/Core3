theme_park_marauder_lizardman = Creature:new {
	objectName = "@npc_name:trandoshan_base_male",
	customName = "Lizardman",
	socialGroup = "",
	mobType = MOB_NPC,
	faction = "",
	level = 10,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 900,
	baseHAMmax = 1000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = INVULNERABLE + CONVERSABLE,
	diet = HERBIVORE,

	templates = {
		"object/mobile/trandoshan_male.iff",
		"object/mobile/dressed_cobral_runner_trandoshan_male_01.iff",
		"object/mobile/dressed_commoner_tatooine_trandoshan_male_01.iff"},
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",

	conversationTemplate = "theme_park_marauder_charal_mission_target_convotemplate",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = brawlernovice,
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(theme_park_marauder_lizardman, "theme_park_marauder_lizardman")
