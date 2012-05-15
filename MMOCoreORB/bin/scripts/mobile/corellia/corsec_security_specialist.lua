corsec_security_specialist = Creature:new {
	objectName = "@mob/creature_names:corsec_detective_aggro",
	socialGroup = "corsec",
	pvpFaction = "corsec",
	faction = "corsec",
	level = 120,
	chanceHit = 4,
	damageMin = 745,
	damageMax = 1200,
	baseXp = 11390,
	baseHAM = 44000,
	baseHAMmax = 54000,
	armor = 2,
	resists = {50,50,30,15,80,30,15,35,-1},
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
		"object/mobile/dressed_corsec_detective_human_male_01.iff",
		"object/mobile/dressed_corsec_detective_human_female_01.iff"},
	lootGroups = {
	  {
			groups = {
				{group = "clothing_attachments", chance = 2500000},
				{group = "armor_attachments", chance = 2500000},
				{group = "corsec_weapons", chance = 2500000},
				{group = "crystals_select", chance = 1250000},
				{group = "color_crystals", chance = 1250000}
			},
			lootChance = 6500000
		}
	},
	weapons = {"corsec_police_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(corsec_security_specialist, "corsec_security_specialist")
