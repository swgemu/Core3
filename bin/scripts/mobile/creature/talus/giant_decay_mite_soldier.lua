giant_decay_mite_soldier = Creature:new {
	objectName = "@mob/creature_names:giant_decay_mite_soldier",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 17,
	chanceHit = 0.310000,
	damageMin = 160,
	damageMax = 170,
	range = 0,
	baseXp = 1102,
	baseHAM = 3900,
	armor = 0,
	resists = {20,20,0,0,0,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 18,
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
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_decay_mite_soldier, "giant_decay_mite_soldier")
