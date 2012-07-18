merek_harvester = Creature:new {
	objectName = "@mob/creature_names:merek_harvester",
	socialGroup = "merek",
	pvpFaction = "",
	faction = "",
	level = 55,
	chanceHit = 0.55,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5281,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {75,-1,10,10,10,-1,10,-1,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/merek_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareacombo",""},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(merek_harvester, "merek_harvester")