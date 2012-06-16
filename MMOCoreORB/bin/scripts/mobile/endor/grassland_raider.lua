grassland_raider = Creature:new {
	objectName = "@mob/creature_names:grassland_raider",
	socialGroup = "endor_marauder",
	pvpFaction = "endor_marauder",
	faction = "endor_marauder",
	level = 40,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4006,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {40,40,30,-1,-1,30,30,30,-1},
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
			"object/mobile/dressed_grassland_blood_marauder.iff",
			"object/mobile/dressed_marauder.iff",
			"object/mobile/dressed_marauder_male.iff",
			"object/mobile/dressed_marauder_male_02.iff",
			"object/mobile/dressed_marauder_male_03.iff",
			"object/mobile/dressed_marauder_female.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(grassland_raider, "grassland_raider")