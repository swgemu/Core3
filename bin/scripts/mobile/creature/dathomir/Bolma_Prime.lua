Bolma_Prime = Creature:new {
	objectName = "Bolma Prime",
	socialGroup = "Bolma",
	pvpFaction = "",
	faction = "",
	level = 37,
	chanceHit = 0.410000,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3642,
	baseHAM = 9900,
	baseHAMmax = 9900,
	armor = 0,
	resists = {45,45,0,0,0,0,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 500,
	hideType = "hide_leathery",
	hideAmount = 550,
	boneType = "bone_mammal",
	boneAmount = 500,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/alpha_bolma.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(Bolma_Prime, "Bolma_Prime")