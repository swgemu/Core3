bol_be = Creature:new {
	objectName = "@mob/creature_names:bol_be",
	socialGroup = "Bol",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.39,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2914,
	baseHAM = 8300,
	baseHAMmax = 10300,
	armor = 0,
	resists = {35,0,-1,0,0,-1,0,-1,-1},
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

	templates = {"object/mobile/bol_hue.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(bol_be, "bol_be")