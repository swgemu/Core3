bordok_be = Creature:new {
	objectName = "bordok be",
	socialGroup = "Bordok",
	pvpFaction = "",
	faction = "",
	level = 1,
	chanceHit = 0.200000,
	damageMin = 30,
	damageMax = 40,
	baseXp = 45,
	baseHAM = 50,
	baseHAMmax = 50,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = HERBIVORE,

	templates = {"object/mobile/bordok_hue.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(bordok_be, "bordok_be")