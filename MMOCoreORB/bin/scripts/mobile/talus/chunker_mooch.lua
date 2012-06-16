chunker_mooch = Creature:new {
	objectName = "@mob/creature_names:chunker_mooch",
	socialGroup = "chunker",
	pvpFaction = "thug",
	faction = "thug",
	level = 7,
	chanceHit = 0.260000,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 270,
	baseHAMmax = 330,
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
	creatureBitmask = PACK,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/dressed_criminal_thug_zabrak_male_01.iff",
				"object/mobile/dressed_goon_twk_male_01.iff",
				"object/mobile/dressed_criminal_thug_human_male_01.iff"},
	lootGroups = {
	    {
	        groups = {
				{group = "junk", chance = 3000000},
				{group = "rifles", chance = 700000},
				{group = "melee_knife", chance = 700000},
				{group = "pistols", chance = 700000},
				{group = "carbines", chance = 700000}
	    	},
			lootChance = 3200000
		}	
	},
	weapons = {"pirate_weapons_light"},
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(chunker_mooch, "chunker_mooch")