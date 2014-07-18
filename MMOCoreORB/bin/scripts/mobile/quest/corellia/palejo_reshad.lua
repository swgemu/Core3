palejo_reshad = Creature:new {
	objectName = "",
	customName = "Palejo Reshad",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 100,
	chanceHit = 1,
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
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_palejo_reshad.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "palejo_reshad_mission_giver_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(palejo_reshad, "palejo_reshad")
