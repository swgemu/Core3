corsec_special_ops_captain = Creature:new {
	objectName = "@mob/creature_names:corsec_captain_aggro",
	socialGroup = "corsec",
	pvpFaction = "corsec",
	faction = "corsec",
	level = 171,
	chanceHit = 11.5,
	damageMin = 995,
	damageMax = 1700,
	baseXp = 16220,
	baseHAM = 110000,
	baseHAMmax = 134000,
	armor = 2,
	resists = {65,65,30,35,80,30,35,35,-1},
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

	templates = {
		"object/mobile/dressed_corsec_captain_human_female_01.iff",
		"object/mobile/dressed_corsec_captain_human_male_01.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "clothing_attachments", chance = 2500000},
				{group = "armor_attachments", chance = 2500000},
				{group = "corsec_weapons", chance = 2500000},
				{group = "crystals_premium", chance = 1250000},
				{group = "color_crystals", chance = 1250000}
			},
			lootChance = 6500000
		}
	},
	weapons = {"corsec_police_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(corsec_special_ops_captain, "corsec_special_ops_captain")
