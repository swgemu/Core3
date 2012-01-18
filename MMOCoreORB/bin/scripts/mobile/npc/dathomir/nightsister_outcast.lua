nightsister_outcast = Creature:new {
	objectName = "@mob/creature_names:nightsister_outcast",
	socialGroup = "Nightsister",
	pvpFaction = "Nightsister",
	faction = "",
	level = 81,
	chanceHit = 0.75,
	damageMin = 555,
	damageMax = 820,
	baseXp = 7761,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 1,
	resists = {30,30,30,100,100,100,100,100,-1},
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
	lootChance = 5400000,

	templates = {"object/mobile/dressed_dathomir_nightsister_outcast.iff"},
	lootgroups = {
		{group = "nightsister_crystals_1", chance = 1000000},
		{group = "nightsister_common", chance = 7500000},
		{group = "pistols", chance = 750000},
		{group = "rifles", chance = 750000}
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(nightsister_outcast, "nightsister_outcast")