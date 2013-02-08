lx_466_dantari = Creature:new {
	objectName = "",
	customName = "(a Dantari tribesman)",	
	socialGroup = "dantari_raiders",
	pvpFaction = "dantari_raiders",
	faction = "dantari_raiders",
	level = 25,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2637,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {25,15,15,15,-1,15,-1,15,-1},
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

	templates = {
		"object/mobile/dantari_male.iff",
		"object/mobile/dantari_female.iff"},
	lootGroups = {},
	weapons = {"primitive_weapons"},
	conversationTemplate = "lx_466_mission_target_convotemplate",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(lx_466_dantari, "lx_466_dantari")
