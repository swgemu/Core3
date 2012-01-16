janta_scout = Creature:new {
	objectName = "@mob/creature_names:janta_scout",
	socialGroup = "Janta Tribe",
	pvpFaction = "Janta Tribe",
	faction = "",
	level = 51,
	chanceHit = 0.55,
	damageMin = 420,
	damageMax = 550,
	baseXp = 5007,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {-1,35,10,10,10,70,10,10,-1},
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

CreatureTemplates:addCreatureTemplate(janta_scout, "janta_scout")