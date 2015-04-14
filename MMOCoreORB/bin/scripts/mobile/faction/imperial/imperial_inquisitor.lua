imperial_inquisitor = Creature:new {
	objectName = "@mob/creature_names:imperial_inquisitor",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "imperial",
	faction = "imperial",
	level = 120,
	chanceHit = 4.000000,
	damageMin = 745,
	damageMax = 1200,
	baseXp = 11296,
	baseHAM = 44000,
	baseHAMmax = 54000,
	armor = 0,
	resists = {50,50,50,0,50,0,50,50,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_inquisitor_human_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 6650000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000},
				{group = "wearables_all", chance = 1000000}
			},
			lootChance = 2800000
		}
	},
	weapons = {"imperial_weapons_heavy"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(riflemanmaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(imperial_inquisitor, "imperial_inquisitor")
