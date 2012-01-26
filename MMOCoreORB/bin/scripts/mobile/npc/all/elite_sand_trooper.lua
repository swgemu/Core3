elite_sand_trooper = Creature:new {
	objectName = "@mob/creature_names:elite_sand_trooper",
	socialGroup = "Imperial.",
	pvpFaction = "Imperial.",
	faction = "",
	level = 44,
	chanceHit = 0.47,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4370,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 0,
	resists = {5,5,40,100,-1,-1,-1,-1,-1},
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

	templates = {"object/mobile/dressed_stormtrooper_black_gold.iff"},
	lootgroups = {},
	weapons = {"stormtrooper_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(elite_sand_trooper, "elite_sand_trooper")