sickle_rasp = Creature:new {
	objectName = "@mob/creature_names:sickle_rasp",
	socialGroup = "Rasp",
	pvpFaction = "",
	faction = "",
	level = 8,
	chanceHit = 0.270000,
	damageMin = 90,
	damageMax = 110,
	baseXp = 235,
	baseHAM = 200,
	baseHAMmax = 200,
	armor = 0,
	resists = {0,0,0,0,0,10,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 15,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/crowned_rasp.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"mildpoison",""},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(sickle_rasp, "sickle_rasp")