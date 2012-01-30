mokk_soothsayer = Creature:new {
	objectName = "@mob/creature_names:mokk_soothsayer",
	socialGroup = "Mokk Tribe",
	pvpFaction = "Mokk Tribe",
	faction = "",
	level = 43,
	chanceHit = 0.44,
	damageMin = 365,
	damageMax = 440,
	baseXp = 4188,
	baseHAM = 93000,
	baseHAMmax = 113000,
	armor = 0,
	resists = {40,60,30,-1,-1,60,60,-1,-1},
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
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dantari_male.iff"},
	lootGroups = {},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(mokk_soothsayer, "mokk_soothsayer")