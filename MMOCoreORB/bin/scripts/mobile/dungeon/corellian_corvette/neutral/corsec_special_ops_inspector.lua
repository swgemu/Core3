corsec_special_ops_inspector = Creature:new {
	objectName = "@mob/creature_names:corsec_inspector_sergeant_aggro",
	socialGroup = "corsec",
	pvpFaction = "corsec",
	faction = "corsec",
	level = 150,
	chanceHit = 8.5,
	damageMin = 895,
	damageMax = 1500,
	baseXp = 14219,
	baseHAM = 81000,
	baseHAMmax = 99000,
	armor = 0,
	resists = {55,55,30,0,80,30,0,35,-1},
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
				{group = "wearables_rare", chance = 1000000},
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

CreatureTemplates:addCreatureTemplate(corsec_special_ops_inspector, "corsec_special_ops_inspector")
