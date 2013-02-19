nightsister_sentinel = Creature:new {
	objectName = "@mob/creature_names:nightsister_sentinal",
	socialGroup = "nightsister",
	pvpFaction = "nightsister",
	faction = "nightsister",
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

	templates = {"object/mobile/dressed_dathomir_nightsister_sentinal.iff"},
	lootGroups = {
		{
			groups = {
				{group = "crystals_quality", chance = 500000},
				{group = "color_crystals", chance = 500000},
				{group = "nightsister_common", chance = 6500000},
				{group = "armor_attachments", chance = 550000},
				{group = "clothing_attachments", chance = 550000},
				{group = "pistols", chance = 700000},
				{group = "rifles", chance = 700000}
			},
			lootChance = 5600000
		}
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = merge(pikemanmaster,brawlermaster,fencermaster)
}

CreatureTemplates:addCreatureTemplate(nightsister_sentinel, "nightsister_sentinel")
