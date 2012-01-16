mercenary_sentry = Creature:new {
	objectName = "mercenary sentry",
	socialGroup = "Geonosian",
	pvpFaction = "Geonosian",
	faction = "",
	level = 66,
	chanceHit = 0.650000,
	damageMin = 470,
	damageMax = 650,
	baseXp = 6380,
	baseHAM = 12000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {40,40,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,
	lootChance = 7500000,

	templates = {"object/mobile/dressed_mercenary_strong_hum_f.iff","object/mobile/dressed_mercenary_strong_hum_m.iff","object/mobile/dressed_mercenary_strong_rod_m.iff","object/mobile/dressed_mercenary_strong_tran_m.iff"},
	lootgroups = {
		{group = "geonosian_common", chance = 5000000},
		{group = "geonosian_hard", chance = 2000000},
		{group = "geonosian_relic", chance = 3000000}
	},
	weapons = {"geonosian_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(mercenary_sentry, "mercenary_sentry")