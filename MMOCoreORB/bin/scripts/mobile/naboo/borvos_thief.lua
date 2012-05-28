borvos_thief = Creature:new {
	objectName = "",
	customName = "Borvo's Thief",
	socialGroup = "borvo",
	pvpFaction = "borvo",
	faction = "borvo",
	level = 17,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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

	templates = {"object/mobile/dressed_borvos_thief.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 3000000},
				{group = "color_crystals", chance = 200000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kit_parts", chance = 500000},
				{group = "rilfes", chance = 1000000},
				{group = "carbines", chance = 1000000}
			},
			lootChance = 3200000
		}					
	},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(borvos_thief, "borvos_thief")