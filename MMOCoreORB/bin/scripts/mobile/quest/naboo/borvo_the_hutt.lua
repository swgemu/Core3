borvo_the_hutt = Creature:new {
	objectName = "@mob/creature_names:borvo_the_hutt",
	socialGroup = "borvo",
	pvpFaction = "borvo",
	faction = "borvo",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9336,
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
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/borvo.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "krayt_dragon_skull_mission_giver_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(borvo_the_hutt, "borvo_the_hutt")
