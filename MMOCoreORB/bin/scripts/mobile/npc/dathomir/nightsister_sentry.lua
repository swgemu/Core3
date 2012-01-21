nightsister_sentry = Creature:new {
	objectName = "@mob/creature_names:nightsister_sentry",
	socialGroup = "Nightsister",
	pvpFaction = "Nightsister",
	faction = "",
	level = 27,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2730,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {15,15,15,60,60,60,60,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,
	lootChance = 4800000,

	templates = {"object/mobile/dressed_dathomir_nightsister_stalker.iff"},
	lootgroups = {
		{group = "nightsister_crystals_1", chance = 1000000},
		{group = "nightsister_common", chance = 6500000},
		{group = "armor_attachments", chance = 550000},
		{group = "clothing_attachments", chance = 550000},
		{group = "pistols", chance = 750000},
		{group = "rifles", chance = 750000}
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(nightsister_sentry, "nightsister_sentry")