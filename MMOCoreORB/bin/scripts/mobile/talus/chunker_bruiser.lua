chunker_bruiser = Creature:new {
	objectName = "@mob/creature_names:chunker_bruiser",
	socialGroup = "chunker",
	pvpFaction = "thug",
	faction = "thug",
	level = 11,
	chanceHit = 0.290000,
	damageMin = 120,
	damageMax = 130,
	baseXp = 514,
	baseHAM = 1000,
	baseHAMmax = 1200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_mugger.iff", 
					"object/mobile/dressed_robber_human_male_01.iff", 
					"object/mobile/dressed_criminal_thug_zabrak_female_01.iff", 
					"object/mobile/dressed_criminal_thug_aqualish_female_02.iff",
					"object/mobile/dressed_criminal_thug_aqualish_male_02.iff",
					"object/mobile/dressed_desperado_bith_female_01.iff",
					"object/mobile/dressed_criminal_thug_human_female_01.iff",
					"object/mobile/dressed_goon_twk_female_01.iff",
					"object/mobile/dressed_criminal_thug_human_male_01.iff",
					"object/mobile/dressed_robber_twk_female_01.iff",
					"object/mobile/dressed_villain_trandoshan_male_01.iff",
					"object/mobile/dressed_desperado_bith_male_01.iff",
					"object/mobile/dressed_mugger.iff"},
	lootGroups = {
	    {
	        groups = {
				{group = "junk", chance = 7200000},
				{group = "rifles", chance = 700000},
				{group = "melee_knife", chance = 700000},
				{group = "pistols", chance = 700000},
				{group = "carbines", chance = 700000}
	    	},
			lootChance = 2200000
		}
	},
	weapons = {"ranged_weapons"},
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(chunker_bruiser, "chunker_bruiser")
