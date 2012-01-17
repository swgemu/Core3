geonosian_technical_assistant = Creature:new {
	objectName = "@mob/creature_names:Geonosian technical assistant",
	socialGroup = "Geonosian",
	pvpFaction = "Geonosian",
	faction = "",
	level = 48,
	chanceHit = 0.49,
	damageMin = 385,
	damageMax = 480,
	baseXp = 4643,
	baseHAM = 10000,
	baseHAMmax = 12200,
	armor = 1,
	resists = {20,20,-1,65,5,30,-1,5,-1},
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
	lootChance = 7500000,

	templates = {},
	lootgroups = {},
	weapons = {"geonosian_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(geonosian_technical_assistant, "geonosian_technical_assistant")