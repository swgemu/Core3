warder = Creature:new {
	objectName = "",
	customName = "a Warder",
	socialGroup = "Wilder",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.35,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2637,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {30,30,0,-1,0,0,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_aakuan_warder_zabrak_male_01.iff"},
	lootgroups = {},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(warder, "warder")