fed_dub_investigator = Creature:new {
	objectName = "@mob/creature_names:fed_dub_investigator",
	socialGroup = "Fed Dub",
	pvpFaction = "Fed Dub",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 150,
	damageMax = 160,
	baseXp = 714,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_fed_dub_investigator_twk_male_01.iff",
					"object/mobile/dressed_fed_dub_investigator_twk_female_01.iff"},
	lootGroups = {},
	weapons = {"imperial_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(fed_dub_investigator, "fed_dub_investigator")