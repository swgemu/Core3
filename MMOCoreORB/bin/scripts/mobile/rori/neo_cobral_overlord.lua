neo_cobral_overlord = Creature:new {
	objectName = "@mob/creature_names:cobral_overlord",
	socialGroup = "cobral",
	pvpFaction = "cobral",
	faction = "cobral",
	level = 33,
	chanceHit = 0.4,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3370,
	baseHAM = 8600,
	baseHAMmax = 10600,
	armor = 0,
	resists = {0,0,0,50,50,50,50,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_cobral_overlord_human_female_01.iff",
		"object/mobile/dressed_cobral_overlord_human_male_01.iff"},

	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 5000000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kits", chance = 4500000}
			},
			lootChance = 5500000
		}					
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(neo_cobral_overlord, "neo_cobral_overlord")