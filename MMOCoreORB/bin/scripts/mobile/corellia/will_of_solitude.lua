will_of_solitude = Creature:new {
	objectName = "@mob/creature_names:will_of_solitude",
	socialGroup = "solitude",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 18,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {10,10,10,-1,10,10,10,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(will_of_solitude, "will_of_solitude")