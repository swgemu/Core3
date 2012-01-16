janta_hunter = Creature:new {
	objectName = "@mob/creature_names:janta_hunter",
	socialGroup = "Janta Tribe",
	pvpFaction = "Janta Tribe",
	faction = "",
	level = 50,
	chanceHit = 0.5,
	damageMin = 415,
	damageMax = 540,
	baseXp = 4916,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {5,5,-1,-1,5,60,-1,-1,-1},
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
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dantari_male.iff"},
	lootgroups = {},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(janta_hunter, "janta_hunter")