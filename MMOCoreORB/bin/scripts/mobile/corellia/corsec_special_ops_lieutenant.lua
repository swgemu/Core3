corsec_special_ops_lieutenant = Creature:new {
	objectName = "@mob/creature_names:corsec_lieutenant_aggro",
	socialGroup = "corsec",
	pvpFaction = "corsec",
	faction = "corsec",
	level = 160,
	chanceHit = 10,
	damageMin = 945,
	damageMax = 1600,
	baseXp = 15170,
	baseHAM = 95000,
	baseHAMmax = 116000,
	armor = 2,
	resists = {55,55,30,35,80,30,35,35,-1},
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

	aiTemplate = "default",

	templates = {
		"object/mobile/dressed_corsec_officer_human_male_01.iff",
		"object/mobile/dressed_corsec_officer_human_female_01.iff"},
	lootGroups = {
	  {
			groups = {
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000},
				{group = "corsec_weapons", chance = 2500000},
				{group = "crystals_premium", chance = 500000},
				{group = "color_crystals", chance = 500000}
			},
			lootChance = 5000000
		}
	},
	weapons = {"corsec_police_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(corsec_special_ops_lieutenant, "corsec_special_ops_lieutenant")
