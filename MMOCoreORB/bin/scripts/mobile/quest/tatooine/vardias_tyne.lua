vardias_tyne = Creature:new {
	objectName = "",
	customName = "Vardias Tyne",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 10,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 810,
	baseHAMmax = 990,
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
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_vardias_tyne.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "vardias_tyne_mission_giver_convotemplate",
	outfit = "vardias_tyne_outfit",
	attacks = {
	}
	
}

CreatureTemplates:addCreatureTemplate(vardias_tyne, "vardias_tyne")
