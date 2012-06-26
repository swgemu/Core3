elite_novatrooper = Creature:new {
	objectName = "@mob/creature_names:stormtrooper_novatrooper_elite",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 162,
	chanceHit = 10,
	damageMin = 945,
	damageMax = 1600,
	baseXp = 15360,
	baseHAM = 95000,
	baseHAMmax = 116000,
	armor = 2,
	resists = {65,65,80,30,35,35,30,45,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_stormtrooper_black_gold.iff"},
	lootGroups = {
		{
			{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 6500000},
				{group = "rifles", chance = 500000},
				{group = "loot_kit_parts", chance = 1300000},
				{group = "carbines", chance = 500000},
				{group = "pistols", chance = 500000},
				{group = "clothing_attachments", chance = 250000},
				{group = "armor_attachments", chance = 250000}
			},
			lootChance = 3000000
		}				
	},
	weapons = {"stormtrooper_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(elite_novatrooper, "elite_novatrooper")