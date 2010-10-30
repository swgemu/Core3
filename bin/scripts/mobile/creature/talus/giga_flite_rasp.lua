giga_flite_rasp = Creature:new {
	objectName = "giga flite rasp",
	socialGroup = "Rasp",
	pvpFaction = "",
	faction = "",
	level = 11,
	chanceHit = 0.290000,
	damageMin = 130,
	damageMax = 140,
	baseXp = 430,
	baseHAM = 900,
	baseHAMmax = 900,
	armor = 0,
	resists = {0,0,0,0,0,15,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 20,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 6,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/flite_rasp.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giga_flite_rasp, "giga_flite_rasp")