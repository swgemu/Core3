crackdown_rebel_liberator = Creature:new {
	objectName = "@mob/creature_names:crackdown_rebel_liberator",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "rebel",
	faction = "rebel",
	level = 41,
	chanceHit = 0.46,
	damageMin = 340,
	damageMax = 450,
	baseXp = 4145,
	baseHAM = 9200,
	baseHAMmax = 11800,
	armor = 0,
	resists = {0,0,40,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
			"object/mobile/dressed_rebel_trooper_twk_male_01.iff",
			"object/mobile/dressed_rebel_trooper_twk_female_01.iff",
			"object/mobile/dressed_rebel_trooper_bith_m_01.iff",
			"object/mobile/dressed_rebel_trooper_human_female_01.iff",
			"object/mobile/dressed_rebel_trooper_human_male_01.iff",
			"object/mobile/dressed_rebel_trooper_sullustan_male_01.iff"
		},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 4700000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "melee_weapons", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000},
				{group = "wearables_common", chance = 1000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(commandonovice,pistoleermaster,carbineermid)
}

CreatureTemplates:addCreatureTemplate(crackdown_rebel_liberator, "crackdown_rebel_liberator")