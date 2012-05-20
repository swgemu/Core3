chunker_swindler = Creature:new {
	objectName = "@mob/creature_names:chunker_swindler",
	socialGroup = "chunker",
	pvpFaction = "thug",
	faction = "thug",
	level = 8,
	chanceHit = 0.270000,
	damageMin = 70,
	damageMax = 75,
	baseXp = 235,
	baseHAM = 405,
	baseHAMmax = 495,
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

	templates = {"object/mobile/dressed_criminal_thug_rodian_female_01.iff",
		"object/mobile/dressed_crook_zabrak_female_01.iff",
		"object/mobile/dressed_criminal_thug_aqualish_female_01.iff"},
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
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(chunker_swindler, "chunker_swindler")