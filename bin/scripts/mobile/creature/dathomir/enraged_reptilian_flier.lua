enraged_reptilian_flier = Creature:new {
	objectName = "enraged reptilian flier",
	socialGroup = "Reptilian Flier",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.350000,
	damageMin = 250,
	damageMax = 260,
	range = 0,
	baseXp = 2730,
	baseHAM = 6550,
	armor = 0,
	resists = {25,30,-1,50,50,-1,50,-1,-1},
	meatType = "meat_avian",
	meatAmount = 135,
	hideType = "hide_leathery",
	hideAmount = 90,
	boneType = "bone_avian",
	boneAmount = 85,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enraged_reptilian_flier, "enraged_reptilian_flier")
