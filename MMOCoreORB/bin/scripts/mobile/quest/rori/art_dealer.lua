art_dealer = Creature:new {
	objectName = "",
	customName = "Art Dealer",
	socialGroup = "",
	faction = "",
	mobType = MOB_NPC,
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 700,
	baseHAMmax = 800,
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
			"object/mobile/dressed_noble_bothan_female_01.iff",
			"object/mobile/dressed_noble_bothan_male_01.iff",
			"object/mobile/dressed_noble_fat_human_female_01.iff",
			"object/mobile/dressed_noble_fat_human_female_02.iff",
			"object/mobile/dressed_noble_fat_human_male_01.iff",
			"object/mobile/dressed_noble_fat_human_male_02.iff",
			"object/mobile/dressed_noble_fat_zabrak_male_01.iff",
			"object/mobile/dressed_noble_fat_zabrak_male_02.iff",
			"object/mobile/dressed_noble_human_female_01.iff",
			"object/mobile/dressed_noble_human_female_02.iff",
			"object/mobile/dressed_noble_human_female_03.iff",
			"object/mobile/dressed_noble_naboo_twilek_female_01.iff",
			"object/mobile/dressed_noble_naboo_twilek_female_02.iff"
				},
	lootGroups = {				
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "rebel_weapons_medium",
	secondaryWeapon = "unarmed",
	conversationTemplate = "ajuva_vanasterin_mission_target_convotemplate",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(brawlernovice,marksmannovice),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(art_dealer, "art_dealer")
