theme_park_marauder_pirate_leader = Creature:new {
	objectName = "@mob/creature_names:marooned_pirate_captain",
	socialGroup = "pirate",
	faction = "pirate",
	level = 24,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2543,
	baseHAM = 3800,
	baseHAMmax = 4200,
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_scarab_pirate_general_twilek_male_01.iff"},
	lootGroups =
	{
		{
			groups = {
				{group = "theme_park_loot_marauder_pirate_rifle", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(theme_park_marauder_pirate_leader, "theme_park_marauder_pirate_leader")
