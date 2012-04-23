rorgungan_commoner = Creature:new {
	objectName = "@mob/creature_names:rorgungan_commoner",
	socialGroup = "Rorgungan",
	pvpFaction = "Rorgungan",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 150,
	damageMax = 160,
	baseXp = 714,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {0,0,0,0,15,0,0,-1,-1},
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
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 4000000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kits", chance = 3500000},
				{group = "color_crystals", chance = 1000000},
				{group = "crystals_poor", chance = 1000000}
			},
			lootChance = 4800000
		}					
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(rorgungan_commoner, "rorgungan_commoner")