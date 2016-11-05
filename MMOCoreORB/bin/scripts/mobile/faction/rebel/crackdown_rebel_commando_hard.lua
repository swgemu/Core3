crackdown_rebel_commando_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_rebel_commando_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "rebel",
	faction = "rebel",
	level = 85,
	chanceHit = 0.86,
	damageMin = 540,
	damageMax = 850,
	baseXp = 8645,
	baseHAM = 18200,
	baseHAMmax = 25200,
	armor = 1,
	resists = {0,0,140,0,0,0,0,-1,-1},
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
			"object/mobile/dressed_rebel_commando_human_female_01.iff",
			"object/mobile/dressed_rebel_commando_human_male_01.iff",
			"object/mobile/dressed_rebel_commando_moncal_male_01.iff",
			"object/mobile/dressed_rebel_commando_rodian_male_01.iff",
			"object/mobile/dressed_rebel_commando_twilek_female_01.iff",
			"object/mobile/dressed_rebel_commando_zabrak_female_01.iff"
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
	attacks = merge(commandomaster,pistoleernovice,carbineermaster,brawlermid)
}

CreatureTemplates:addCreatureTemplate(crackdown_rebel_commando_hard, "crackdown_rebel_commando_hard")