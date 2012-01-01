stormtrooper_captain = Creature:new {
	objectName = "@mob/creature_names:stormtrooper_captain",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 29,
	chanceHit = 3.08,
	damageMin = 280,
	damageMax = 290,
	baseXp = 3005,
	baseHAM = 8300,
	baseHAMmax = 10100,
	armor = 0,
	resists = {0,0,0,-1,30,-1,30,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_stormtrooper_captain_black_black.iff"},
	lootgroups = {},
	weapons = {"stormtrooper_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(stormtrooper_captain, "stormtrooper_captain")