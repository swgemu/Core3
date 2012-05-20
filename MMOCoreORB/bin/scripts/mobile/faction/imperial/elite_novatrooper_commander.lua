elite_novatrooper_commander = Creature:new {
	objectName = "@mob/creature_names:stormtrooper_novatrooper_elite_commander",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 201,
	chanceHit = 16,
	damageMin = 1145,
	damageMax = 2000,
	baseXp = 19104,
	baseHAM = 160000,
	baseHAMmax = 195000,
	armor = 3,
	resists = {60,75,80,30,5,5,30,45,-1},
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

	templates = {"object/mobile/dressed_stormtrooper_commander_black_gold.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 3600000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 4000000
		}			
	},
	weapons = {"stormtrooper_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(elite_novatrooper_commander, "elite_novatrooper_commander")