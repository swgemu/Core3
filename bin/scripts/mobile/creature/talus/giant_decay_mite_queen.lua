giant_decay_mite_queen = Creature:new {
	objectName = "@mob/creature_names:giant_decay_mite_queen",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.350000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2637,
	baseHAM = 8000,
	armor = 0,
	resists = {40,40,0,0,0,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 28,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"mediumdisease",""},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_decay_mite_queen, "giant_decay_mite_queen")
