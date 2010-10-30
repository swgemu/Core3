merek_harvester = Creature:new {
	objectName = "@mob/creature_names:merek_harvester",
	socialGroup = "Merek",
	pvpFaction = "",
	faction = "",
	level = 55,
	chanceHit = 0.550000,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5281,
	baseHAM = 12500,
	baseHAMmax = 12500,
	armor = 0,
	resists = {75,-1,0,0,0,-1,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/merek.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareacombo",""},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(merek_harvester, "merek_harvester")