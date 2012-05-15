minion_of_lord_nyax = Creature:new {
	objectName = "@mob/creature_names:lord_nyax_minion",
	socialGroup = "followers_of_lord_nyax",
	pvpFaction = "followers_of_lord_nyax",
	faction = "followers_of_lord_nyax",
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
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_criminal_smuggler_human_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "nyax", chance = 2000000},
				{group = "pistols", chance = 4000000},
				{group = "rifles", chance = 4000000}
			},
			lootChance = 3500000
		}
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(minion_of_lord_nyax, "minion_of_lord_nyax")
