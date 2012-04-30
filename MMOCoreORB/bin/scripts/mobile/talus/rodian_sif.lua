rodian_sif = Creature:new {
	objectName = "",
	customName = "a rodian Sif",
	socialGroup = "Sif",
	pvpFaction = "Sif",
	faction = "",
	level = 37,
	chanceHit = 0.42,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3733,
	baseHAM = 9000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {40,40,0,-1,0,-1,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_talus_sif_mercenary_rodian_02.iff"},
	lootGroups = {},
	weapons = {"sif_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(rodian_sif, "rodian_sif")