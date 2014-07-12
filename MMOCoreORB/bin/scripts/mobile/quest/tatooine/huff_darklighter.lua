huff_darklighter = Creature:new {
	objectName = "",
	customName = "Huff Darklighter",
	socialGroup = "darklighter",
	pvpFaction = "",
	faction = "",
	level = 99,
	chanceHit = 0.99,
	damageMin = 640,
	damageMax = 990,
	baseXp = 9243,
	baseHAM = 24000,
	baseHAMmax = 29000,
	armor = 0,
	resists = {40,40,0,0,0,0,0,0,-1},
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
	creatureBitmask = HERD,
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/huff_darklighter.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "krayt_dragon_skull_mission_giver_convotemplate",
	outfit = "huff_darklighter_outfit",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(huff_darklighter, "huff_darklighter")