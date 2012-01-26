brigand_scout = Creature:new {
	objectName = "@mob/creature_names:brigand",
	socialGroup = "Brigand",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 714,
	baseHAM = 2000,
	baseHAMmax = 2400,
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
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(brigand_scout, "brigand_scout")