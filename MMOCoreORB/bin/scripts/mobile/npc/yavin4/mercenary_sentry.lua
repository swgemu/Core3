mercenary_sentry = Creature:new {
	objectName = "@mob/creature_names:geonosian_human_security_force",
	socialGroup = "Geonosian",
	pvpFaction = "Geonosian",
	faction = "",
	level = 66,
	chanceHit = 0.65,
	damageMin = 470,
	damageMax = 650,
	baseXp = 6380,
	baseHAM = 12000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {40,40,20,20,20,20,20,-1,-1},
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
	lootChance = 5500000,

	templates = {"object/mobile/dressed_mercenary_strong_hum_f.iff","object/mobile/dressed_mercenary_strong_hum_m.iff","object/mobile/dressed_mercenary_strong_rod_m.iff","object/mobile/dressed_mercenary_strong_tran_m.iff"},
	lootgroups = {
		{group = "geonosian_hard", chance = 2500000},
		{group = "geonosian_common", chance = 4500000},
		{group = "geonosian_relic", chance = 3000000}
	},
	weapons = {"geonosian_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(mercenary_sentry, "mercenary_sentry")