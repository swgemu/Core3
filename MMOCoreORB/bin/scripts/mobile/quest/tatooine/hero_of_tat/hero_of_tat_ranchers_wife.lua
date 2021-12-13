hero_of_tat_ranchers_wife = Creature:new {
	objectName = "@mob/creature_names:quest_hero_of_tatooine_wife",
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
		"object/mobile/dressed_commoner_tatooine_aqualish_female_01.iff",
		"object/mobile/dressed_commoner_tatooine_aqualish_female_02.iff",
		"object/mobile/dressed_commoner_tatooine_aqualish_female_03.iff",
		"object/mobile/dressed_commoner_tatooine_aqualish_female_04.iff",
		"object/mobile/dressed_commoner_tatooine_aqualish_female_05.iff",
		"object/mobile/dressed_commoner_tatooine_aqualish_female_06.iff",
		"object/mobile/dressed_commoner_tatooine_aqualish_female_07.iff",
		"object/mobile/dressed_commoner_tatooine_aqualish_female_08.iff",
		"object/mobile/dressed_commoner_tatooine_bith_female_01.iff",
		"object/mobile/dressed_commoner_tatooine_bith_female_02.iff",
		"object/mobile/dressed_commoner_tatooine_bith_female_03.iff",
		"object/mobile/dressed_commoner_tatooine_bith_female_04.iff",
		"object/mobile/dressed_commoner_tatooine_bith_female_05.iff",
		"object/mobile/dressed_commoner_tatooine_bith_female_06.iff",
		"object/mobile/dressed_commoner_tatooine_rodian_female_01.iff",
		"object/mobile/dressed_commoner_tatooine_rodian_female_02.iff",
		"object/mobile/dressed_commoner_tatooine_rodian_female_03.iff",
		"object/mobile/dressed_commoner_tatooine_rodian_female_04.iff",
		"object/mobile/dressed_commoner_tatooine_trandoshan_female_01.iff",
		"object/mobile/dressed_commoner_tatooine_trandoshan_female_02.iff",
		"object/mobile/dressed_commoner_tatooine_trandoshan_female_03.iff",
		"object/mobile/dressed_commoner_tatooine_trandoshan_female_04.iff",
	},
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "heroOfTatRanchersWifeConvoTemplate",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(marksmannovice,brawlernovice),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(hero_of_tat_ranchers_wife, "hero_of_tat_ranchers_wife")
