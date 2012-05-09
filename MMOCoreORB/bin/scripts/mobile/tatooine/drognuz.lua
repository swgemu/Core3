drognuz = Creature:new {
	objectName = "",
	customName = "Drognuz",
	socialGroup = "Jabba",
	pvpFaction = "Jabba",
	faction = "",
	level = 14,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 650,
	baseHAM = 2550,
	baseHAMmax = 2700,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/gamorrean.iff"},
	lootGroups = {},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(drognuz, "drognuz")