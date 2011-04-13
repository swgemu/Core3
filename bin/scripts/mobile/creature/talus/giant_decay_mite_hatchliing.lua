giant_decay_mite_hatchliing = Creature:new {
	objectName = "giant decay mite hatchliing",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 7,
	chanceHit = 0.250000,
	damageMin = 50,
	damageMax = 55,
	baseXp = 187,
	baseHAM = 125,
	baseHAMmax = 125,
	armor = 0,
	resists = {10,10,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 5,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/decay_mite.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_decay_mite_hatchliing, "giant_decay_mite_hatchliing")