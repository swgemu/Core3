chunker_nitwit = Creature:new {
	objectName = "@mob/creature_names:chunker_nitwit",
	socialGroup = "Chunker Gang",
	pvpFaction = "",
	faction = "",
	level = 5,
	chanceHit = 0.250000,
	damageMin = 45,
	damageMax = 50,
	baseXp = 85,
	baseHAM = 135,
	baseHAMmax = 165,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
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
				{group = "junk", chance = 2000000},
				{group = "rifles", chance = 2000000},
				{group = "melee_knife", chance = 2000000},
				{group = "pistols", chance = 2000000},
				{group = "carbines", chance = 2000000}
	    	},
			lootChance = 5000000
		}	
	},
	weapons = {"pirate_weapons_light"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(chunker_nitwit, "chunker_nitwit")