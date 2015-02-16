theme_park_marauder_ewok_pelt = Creature:new {
	objectName = "@mob/creature_names:masterful_ewok_warrior",
	socialGroup = "gondula_tribe",
	faction = "gondula_tribe",
	level = 21,
	chanceHit = 0.28,
	damageMin = 200,
	damageMax = 300,
	baseXp = 988,
	baseHAM = 3000,
	baseHAMmax = 3200,
	armor = 0,
	resists = {5,5,0,15,15,0,0,-1,-1},
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

	templates = {"object/mobile/dressed_ewok_f_03.iff"},
	lootGroups =
	{
		{
			groups = {
				{group = "theme_park_loot_marauder_ewok_pelt", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {"ewok_weapons"},
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(theme_park_marauder_ewok_pelt, "theme_park_marauder_ewok_pelt")
