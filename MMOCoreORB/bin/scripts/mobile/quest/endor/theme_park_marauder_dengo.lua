theme_park_marauder_dengo = Creature:new {
	objectName = "@mob/creature_names:marooned_pirate_captain",
	customName = "Dengo Haribonn",
	socialGroup = "pirate",
	faction = "pirate",
	level = 12,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2543,
	baseHAM = 1200,
	baseHAMmax = 1500,
	armor = 0,
	resists = {20,20,10,40,-1,40,10,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_scarab_pirate_general_human_male_01.iff"},
	lootGroups =
	{
		{
			groups = {
				{group = "theme_park_loot_marauder_commlink", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(theme_park_marauder_dengo, "theme_park_marauder_dengo")
