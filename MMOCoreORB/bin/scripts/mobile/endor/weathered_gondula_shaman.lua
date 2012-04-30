weathered_gondula_shaman = Creature:new {
	objectName = "@mob/creature_names:weathered_gondula_shaman",
	socialGroup = "Condula Tribe",
	pvpFaction = "Condula Tribe",
	faction = "",
	level = 43,
	chanceHit = 0.45,
	damageMin = 350,
	damageMax = 410,
	baseXp = 4188,
	baseHAM = 9400,
	baseHAMmax = 11400,
	armor = 0,
	resists = {40,40,30,30,60,60,30,30,-1},
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

	templates = {"object/mobile/dressed_ewok_m_04.iff"},
	lootGroups = {},
	weapons = {"ewok_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(weathered_gondula_shaman, "weathered_gondula_shaman")