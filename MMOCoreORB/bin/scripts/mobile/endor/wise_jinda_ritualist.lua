wise_jinda_ritualist = Creature:new {
	objectName = "@mob/creature_names:wise_jinda_ritualist",
	socialGroup = "jinda_tribe",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.41,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3460,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {25,25,25,25,25,25,25,25,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/jinda_male.iff",
			"object/mobile/jinda_female.iff",
			"object/mobile/jinda_male_01.iff",
			"object/mobile/jinda_female_01.iff"},

	lootGroups = {
		 {
	        groups = {
				{group = "ewok", chance = 8100000},
				{group = "wearables_uncommon", chance = 1000000},
				{group = "armor_attachments", chance = 450000},
				{group = "clothing_attachments", chance = 450000},
			},
			lootChance = 2500000
		},
	},
	weapons = {"ewok_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,brawlermaster)

}

CreatureTemplates:addCreatureTemplate(wise_jinda_ritualist, "wise_jinda_ritualist")
