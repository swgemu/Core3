logro_elsin = Creature:new {
	objectName = "@npc_spawner_n:logro_elsin",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 23,
	chanceHit = 0.33,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2006,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {30,30,-1,0,0,-1,0,-1,-1},
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
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tie_fighter_m.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(logro_elsin, "logro_elsin")