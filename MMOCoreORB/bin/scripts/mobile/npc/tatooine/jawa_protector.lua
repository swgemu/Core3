jawa_protector = Creature:new {
	objectName = "@mob/creature_names:jawa_protector",
	socialGroup = "Jawa",
	pvpFaction = "Jawa",
	faction = "",
	level = 17,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1257,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {15,10,-1,0,0,-1,0,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
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
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(jawa_protector, "jawa_protector")