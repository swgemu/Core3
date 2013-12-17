farmer = Creature:new {
	objectName = "@mob/creature_names:farmer",
	generateRandomName =true,
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
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
	pvpBitmask = NONE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
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
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(farmer, "farmer")
