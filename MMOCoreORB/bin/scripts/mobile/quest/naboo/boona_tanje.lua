boona_tanje = Creature:new {
	objectName = "",
	socialGroup = "nomad",
	faction = "naboo",
	mobType = MOB_NPC,
	level = 6,
	chanceHit = 0.25,
	damageMin = 50,
	damageMax = 55,
	baseXp = 147,
	baseHAM = 180,
	baseHAMmax = 220,
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
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_commoner_naboo_bothan_female_01.iff",
			"object/mobile/dressed_commoner_naboo_bothan_female_02.iff",
			"object/mobile/dressed_commoner_naboo_human_female_01.iff",
			"object/mobile/dressed_commoner_naboo_human_female_02.iff",
			"object/mobile/dressed_commoner_naboo_human_female_03.iff",
			"object/mobile/dressed_commoner_naboo_human_female_04.iff",
			"object/mobile/dressed_commoner_naboo_human_female_05.iff",
			"object/mobile/dressed_commoner_naboo_human_female_06.iff",
			"object/mobile/dressed_commoner_naboo_human_female_07.iff",
			"object/mobile/dressed_commoner_naboo_human_female_08.iff",
			"object/mobile/dressed_commoner_naboo_moncal_female_01.iff",
			"object/mobile/dressed_commoner_naboo_moncal_female_02.iff",
			"object/mobile/dressed_commoner_naboo_twilek_female_01.iff",
			"object/mobile/dressed_commoner_naboo_twilek_female_02.iff",
			"object/mobile/dressed_commoner_naboo_zabrak_female_01.iff",
			"object/mobile/dressed_commoner_naboo_zabrak_female_02.iff"},
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "rep_been_mission_target_convotemplate",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = {},
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(boona_tanje, "boona_tanje")
