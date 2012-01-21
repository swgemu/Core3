nightsister_sentinel = Creature:new {
	objectName = "@mob/creature_names:nightsister_sentinal",
	socialGroup = "Nightsister",
	pvpFaction = "Nightsister",
	faction = "",
	level = 88,
	chanceHit = 0.8,
	damageMin = 545,
	damageMax = 800,
	baseXp = 8408,
	baseHAM = 21000,
	baseHAMmax = 26000,
	armor = 1,
	resists = {45,45,45,100,100,100,100,100,-1},
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
	lootChance = 5600000,

	templates = {"object/mobile/dressed_dathomir_spider_nightsister_sentinel.iff"},
	lootgroups = {
		{group = "nightsister_crystals_2", chance = 1000000},
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

CreatureTemplates:addCreatureTemplate(nightsister_sentinel, "nightsister_sentinel")