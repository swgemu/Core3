chunker_creep = Creature:new {
	objectName = "@mob/creature_names:chunker_creep",
	socialGroup = "chunker",
	pvpFaction = "thug",
	faction = "thug",
	level = 9,
	chanceHit = 0.270000,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 675,
	baseHAMmax = 825,
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
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {},
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

CreatureTemplates:addCreatureTemplate(chunker_creep, "chunker_creep")