puss_covered_decay_mite_soldier = Creature:new {
	objectName = "@mob/creature_names:puss_covered_decay_mite_soldier",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.300000,
	damageMin = 150,
	damageMax = 160,
	baseXp = 831,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {15,15,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/decay_mite.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(puss_covered_decay_mite_soldier, "puss_covered_decay_mite_soldier")