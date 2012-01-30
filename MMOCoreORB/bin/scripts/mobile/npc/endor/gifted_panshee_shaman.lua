gifted_panshee_shaman = Creature:new {
	objectName = "@mob/creature_names:gifted_panshee_shaman",
	socialGroup = "Panshee Tribe",
	pvpFaction = "Panshee Tribe",
	faction = "",
	level = 38,
	chanceHit = 0.42,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3733,
	baseHAM = 9200,
	baseHAMmax = 11200,
	armor = 0,
	resists = {25,25,25,25,25,25,25,25,-1},
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
	creatureBitmask = PACK + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/ewok_male.iff"},
	lootGroups = {},
	weapons = {"ewok_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(gifted_panshee_shaman, "gifted_panshee_shaman")