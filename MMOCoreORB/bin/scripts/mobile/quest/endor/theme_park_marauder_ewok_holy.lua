theme_park_marauder_ewok_holy = Creature:new {
	objectName = "@npc_name:ewok_base_male",
	customName = "Ewok Holy One",
	socialGroup = "gondula_tribe",
	faction = "gondula_tribe",
	level = 34,
	chanceHit = 0.35,
	damageMin = 400,
	damageMax = 550,
	baseXp = 4000,
	baseHAM = 9000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {30,30,30,30,30,30,30,-1,-1},
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

	templates = {"object/mobile/dressed_ewok_m_07.iff"},
	lootGroups =
	{
		{
			groups = {
				{group = "theme_park_loot_marauder_ewok_staff", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {"ewok_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(theme_park_marauder_ewok_holy, "theme_park_marauder_ewok_holy")
