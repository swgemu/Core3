deliver_npc = Creature:new {
	objectName = "",
	socialGroup = "",
	faction = "",
	mobType = MOB_NPC,
	level = 100,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2914,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {-1,-1,-1,-1,-1,-1,-1,-1,-1},
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
	creatureBitmask = NONE,
	optionsBitmask = INVULNERABLE + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_commoner_fat_zabrak_male_01.iff","object/mobile/dressed_commoner_fat_zabrak_male_02.iff","object/mobile/dressed_commoner_fat_zabrak_female_01.iff","object/mobile/dressed_commoner_fat_zabrak_female_02.iff","object/mobile/dressed_commoner_fat_human_male_01.iff","object/mobile/dressed_commoner_fat_human_male_02.iff","object/mobile/dressed_commoner_fat_human_female_01.iff","object/mobile/dressed_commoner_fat_human_female_02.iff","object/mobile/dressed_commoner_fat_twilek_male_01.iff","object/mobile/dressed_commoner_fat_twilek_male_02.iff","object/mobile/dressed_commoner_fat_twilek_female_01.iff","object/mobile/dressed_commoner_fat_twilek_female_02.iff","object/mobile/dressed_commoner_old_zabrak_male_01.iff","object/mobile/dressed_commoner_old_zabrak_male_02.iff","object/mobile/dressed_commoner_old_zabrak_female_01.iff","object/mobile/dressed_commoner_old_zabrak_female_02.iff","object/mobile/dressed_commoner_old_human_male_01.iff","object/mobile/dressed_commoner_old_human_male_02.iff","object/mobile/dressed_commoner_old_human_female_01.iff","object/mobile/dressed_commoner_old_human_female_02.iff","object/mobile/dressed_commoner_old_twilek_male_01.iff","object/mobile/dressed_commoner_old_twilek_male_02.iff","object/mobile/dressed_commoner_old_twilek_female_01.iff","object/mobile/dressed_commoner_old_twilek_female_02.iff"},
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "deliver_npc",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = {},
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(deliver_npc, "deliver_npc")
