theme_park_marauder_stranded_mercenary = Creature:new {
	objectName = "",
	customName = "a stranded mercenary",
	socialGroup = "",
	faction = "",
	level = 35,
	chanceHit = 0.35,
	damageMin = 300,
	damageMax = 400,
	baseXp = 3500,
	baseHAM = 6800,
	baseHAMmax = 7200,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
			"object/mobile/dressed_mercenary_warlord_hum_m.iff",
			"object/mobile/dressed_mercenary_elite_hum_m.iff",
			"object/mobile/dressed_mercenary_destroyer_wee_m.iff",
			"object/mobile/dressed_mercenary_commander_nikto_m.iff"
			},
	lootGroups =
	{
		{ groups =
			{ {group = "theme_park_loot_marauder_hyperdrive", chance = 10000000} },
			lootChance = 10000000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(theme_park_marauder_stranded_mercenary, "theme_park_marauder_stranded_mercenary")
