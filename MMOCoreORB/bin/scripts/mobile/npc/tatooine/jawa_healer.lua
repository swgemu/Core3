jawa_healer = Creature:new {
	objectName = "@mob/creature_names:jawa_healer",
	socialGroup = "Jawa",
	pvpFaction = "Jawa",
	faction = "",
	level = 10,
	chanceHit = 0.28,
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
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/jawa_male.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 5000000},
				{group = "color_crystals", chance = 400000},
				{group = "crystals_good", chance = 300000},
				{group = "pistols", chance = 1600000},
				{group = "rifles", chance = 1600000},
				{group = "carbines", chance = 1100000}
			},
			lootChance = 5500000
		}				
	},
	weapons = {"rebel_weapons_light"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(jawa_healer, "jawa_healer")