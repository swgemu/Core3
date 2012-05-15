grassland_raider = Creature:new {
	objectName = "@mob/creature_names:grassland_raider",
	socialGroup = "Marauder",
	pvpFaction = "Marauder",
	faction = "",
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

	templates = {"object/mobile/dressed_grassland_blood_marauder.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(grassland_raider, "grassland_raider")