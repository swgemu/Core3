vesp_hunter = Creature:new {
	objectName = "@mob/creature_names:vesp_hunter",
	socialGroup = "Vesp",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2543,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "meat_reptilian",
	meatAmount = 10,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 0,
	diet = CARNIVORE,

	templates = {"object/mobile/vesp.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(vesp_hunter, "vesp_hunter")