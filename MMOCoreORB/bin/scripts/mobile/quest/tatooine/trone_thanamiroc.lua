trone_thanamiroc = Creature:new {
	objectName = "",
	socialGroup = "",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2219,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {0,20,0,-1,-1,50,50,-1,-1},
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
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_criminal_assassin_human_male_01.iff",
		"object/mobile/tusken_raider.iff",
		"object/mobile/dressed_quest_farmer.iff",
		"object/mobile/dressed_commoner_tatooine_nikto_male_01.iff",
		"object/mobile/dressed_criminal_pirate_human_male_01.iff",
		"object/mobile/dressed_criminal_slicer_human_male_01.iff",
		"object/mobile/dressed_diplomat_human_male_01.iff",
		"object/mobile/dressed_diplomat_human_male_02.iff",
		"object/mobile/dressed_diplomat_human_male_03.iff",
	},
	lootGroups = {
		{
			groups = {
				{group = "task_loot_bren_kingal_atst_pilots_helmet", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(marksmanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(trone_thanamiroc, "trone_thanamiroc")
