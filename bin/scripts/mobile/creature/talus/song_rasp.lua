song_rasp = Creature:new {
	objectName = "@mob/creature_names:song_rasp",
	socialGroup = "Rasp",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.280000,
	damageMin = 90,
	damageMax = 100,
	baseXp = 356,
	baseHAM = 900,
	baseHAMmax = 900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 10,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 3,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/flite_rasp.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(song_rasp, "song_rasp")