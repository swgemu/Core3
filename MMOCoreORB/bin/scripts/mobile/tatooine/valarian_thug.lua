valarian_thug = Creature:new {
	objectName = "@mob/creature_names:valarian_thug",
	socialGroup = "valarian",
	pvpFaction = "valarian",
	faction = "valarian",
	level = 11,
	chanceHit = 0.29,
	damageMin = 120,
	damageMax = 130,
	baseXp = 430,
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
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_tatooine_valarian_thug.iff",
		"object/mobile/dressed_criminal_thug_aqualish_female_01.iff",
		"object/mobile/dressed_criminal_thug_aqualish_female_01.iff"
	},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 3000000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kit_parts", chance = 1500000}
			},
			lootChance = 3500000
		}				
	},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(valarian_thug, "valarian_thug")
