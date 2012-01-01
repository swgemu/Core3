tusken_king = Creature:new {
	objectName = "@mob/creature_names:tusken_king",
	socialGroup = "Tusken Raider",
	pvpFaction = "Tusken Raider",
	faction = "",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9522,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 0,
	resists = {45,35,0,80,-1,50,0,0,-1},
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
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/tusken_raider.iff"},
	lootgroups = {},
	weapons = {"tusken_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(tusken_king, "tusken_king")