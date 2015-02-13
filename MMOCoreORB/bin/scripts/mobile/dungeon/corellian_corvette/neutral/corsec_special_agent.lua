corsec_special_agent = Creature:new {
	objectName = "@mob/creature_names:corsec_agent_aggro",
	socialGroup = "corsec",
	pvpFaction = "corsec",
	faction = "corsec",
	level = 105,
	chanceHit = 1.75,
	damageMin = 670,
	damageMax = 1050,
	baseXp = 9987,
	baseHAM = 29000,
	baseHAMmax = 36000,
	armor = 2,
	resists = {45,45,30,5,80,30,5,35,-1},
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

	templates = { "object/mobile/dressed_corsec_pilot_human_female_01.iff",
			"object/mobile/dressed_corsec_pilot_human_male_01.iff"},
	lootGroups = {
	  {
			groups = {
				{group = "junk", chance = 6500000},
				{group = "clothing_attachments", chance = 250000},
				{group = "armor_attachments", chance = 250000},
				{group = "corsec_weapons", chance = 2500000},
				{group = "crystals_select", chance = 250000},
				{group = "color_crystals", chance = 250000}
			},
			lootChance = 3300000
		}
	},
	weapons = {"corsec_police_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(corsec_special_agent, "corsec_special_agent")
