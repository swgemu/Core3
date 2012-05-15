govenor = Creature:new {
	objectName = "@mob/creature_names:govenor",
	socialGroup = "naboo",
	pvpFaction = "naboo",
	faction = "naboo",
	level = 9,
	chanceHit = 0.27,
	damageMin = 675,
	damageMax = 825,
	baseXp = 235,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_governor.iff"},
	lootGroups = {},
	weapons = {""},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(govenor, "govenor")