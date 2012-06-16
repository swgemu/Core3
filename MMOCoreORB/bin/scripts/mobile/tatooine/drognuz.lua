drognuz = Creature:new {
	objectName = "",
	customName = "Drognuz",
	socialGroup = "jabba",
	pvpFaction = "jabba",
	faction = "jabba",
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

	aiTemplate = "default",

	templates = {"object/mobile/gamorrean.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(drognuz, "drognuz")