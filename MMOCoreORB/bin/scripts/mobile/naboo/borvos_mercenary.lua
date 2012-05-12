borvos_mercenary = Creature:new {
	objectName = "@mob/creature_names:borvos_mercenary",
	socialGroup = "borvo",
	pvpFaction = "borvo",
	faction = "borvo",
	level = 12,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 514,
	baseHAM = 1200,
	baseHAMmax = 1400,
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

	templates = {"object/mobile/dressed_borvos_mercenary.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 4000000},
				{group = "color_crystals", chance = 500000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kits", chance = 1500000},
				{group = "rilfes", chance = 1750000},
				{group = "carbines", chance = 1750000}
			},
			lootChance = 4800000
		}				
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(borvos_mercenary, "borvos_mercenary")