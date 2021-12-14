gramm_surveyor = Creature:new {
	objectName = "",
	socialGroup = "townsperson",
	faction = "townsperson",
	mobType = MOB_NPC,
	level = 4,
	chanceHit = 0.24,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 138,
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
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_quest_farmer.iff",
		"object/mobile/dressed_commoner_naboo_zabrak_male_02.iff",
		"object/mobile/dressed_commoner_tatooine_rodian_female_03.iff",
		"object/mobile/dressed_commoner_naboo_human_male_02.iff",
		"object/mobile/dressed_commoner_fat_twilek_female_02.iff",
		"object/mobile/dressed_commoner_tatooine_sullustan_male_05.iff",
		"object/mobile/dressed_commoner_tatooine_nikto_male_01.iff",
		"object/mobile/dressed_commoner_fat_zabrak_female_01.iff",
		"object/mobile/dressed_commoner_fat_human_male_01.iff"
	},
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "gramm_rile_mission_target_convotemplate",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = brawlermaster,
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(gramm_surveyor, "gramm_surveyor")
