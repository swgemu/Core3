lutin_nightstalker = Creature:new {
	objectName = "",
	customName = "Lutin Nightstalker",
	socialGroup = "Rebel",
	pvpFaction = "",
	faction = "Rebel",
	level = 99,
	chanceHit = 0.99,
	damageMin = 640,
	damageMax = 990,
	baseXp = 9336,
	baseHAM = 24000,
	baseHAMmax = 29000,
	armor = 2,
	resists = {45,45,45,90,90,90,45,45,45},
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
	creatureBitmask = PACK,
	optionsBitmask = 264,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_rebel_general_moncal_male_01.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "lutin_nightstalker_conv",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(lutin_nightstalker, "lutin_nightstalker")