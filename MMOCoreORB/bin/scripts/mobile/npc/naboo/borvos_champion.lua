borvos_champion = Creature:new {
	objectName = "@mob/creature_names:borvos_champion",
	socialGroup = "Borvo",
	pvpFaction = "Borvo",
	faction = "",
	level = 21,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2006,
	baseHAM = 5400,
	baseHAMmax = 6600,
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_borvos_champion.iff"},
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
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(borvos_champion, "borvos_champion")