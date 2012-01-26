veers = Creature:new {
	objectName = "",
	customName = "Veers",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 25,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2637,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {0,20,0,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/veers.iff"},
	lootgroups = {},
	weapons = {"imperial_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(veers, "veers")