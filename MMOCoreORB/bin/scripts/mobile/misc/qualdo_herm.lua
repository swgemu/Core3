qualdo_herm = Creature:new {
	objectName = "@mob/creature_names:qualdo_herm",
	socialGroup = "rebel",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 100,
	chanceHit = 1.000000,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9429,
	baseHAM = 24000,
	baseHAMmax = 30000,
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
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_qualdo_herm.iff"},
	lootGroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(qualdo_herm, "qualdo_herm")