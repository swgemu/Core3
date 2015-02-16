corsec_special_ops_comissioner = Creature:new {
	objectName = "@mob/creature_names:corsec_commissioner_aggro",
	socialGroup = "corsec",
	faction = "corsec",
	level = 226,
	chanceHit = 19.75,
	damageMin = 1270,
	damageMax = 2250,
	baseXp = 21533,
	baseHAM = 208000,
	baseHAMmax = 254000,
	armor = 3,
	resists = {85,85,30,10,80,30,10,35,-1},
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

	templates = { "object/mobile/dressed_corsec_detective_human_male_01.iff",
			"object/mobile/dressed_corsec_detective_human_female_01.iff"},
	lootGroups = {
	  {
			groups = {
				{group = "junk", chance = 4500000},
				{group = "wearables_scarce", chance = 1000000},
                                {group = "clothing_attachments", chance = 250000},
				{group = "armor_attachments", chance = 250000},
				{group = "corsec_weapons", chance = 2500000},
				{group = "crystals_premium", chance = 650000},
				{group = "color_crystals", chance = 850000}
			},
			lootChance = 3300000
		}
	},
	weapons = {"corsec_police_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(corsec_special_ops_comissioner, "corsec_special_ops_comissioner")
