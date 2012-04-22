novatrooper_commander = Creature:new {
	objectName = "@mob/creature_names:stormtrooper_novatrooper_commander",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "imperial",
	level = 182,
	chanceHit = 13,
	damageMin = 1045,
	damageMax = 1800,
	baseXp = 17274,
	baseHAM = 126000,
	baseHAMmax = 154000,
	armor = 0,
	resists = {65,65,80,30,0,0,30,45,-1},
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
				{group = "rifles", chance = 2000000},
				{group = "pistols", chance = 2000000},
				{group = "clothing_attachments", chance = 1100000},
				{group = "armor_attachments", chance = 1100000}
			},
			lootChance = 4000000
		}		
	},
	weapons = {"stormtrooper_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(novatrooper_commander, "novatrooper_commander")