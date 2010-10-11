sickly_decay_mite_queen = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:sickly_decay_mite_queen",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.330000,
	damageMin = 220,
	damageMax = 230,
	range = 25,
	baseXp = 1609,
	baseHAM = 3900,
	armor = 0,
	resists = {0,25,-1,-1,-1,-1,30,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(sickly_decay_mite_queen, "sickly_decay_mite_queen")
