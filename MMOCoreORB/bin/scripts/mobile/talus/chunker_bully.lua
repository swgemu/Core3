chunker_bully = Creature:new {
	objectName = "@mob/creature_names:chunker_bully",
	socialGroup = "chunker",
	pvpFaction = "thug",
	faction = "thug",
	level = 10,
	chanceHit = 0.280000,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 810,
	baseHAMmax = 990,
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
	creatureBitmask = PACK + STALKER,
	diet = HERBIVORE,

	templates = {},
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
	weapons = {"ranged_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(chunker_bully, "chunker_bully")