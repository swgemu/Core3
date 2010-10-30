bolma_male = Creature:new {
	objectName = "bolma male",
	socialGroup = "Bolma",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.370000,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2730,
	baseHAM = 9000,
	baseHAMmax = 9000,
	armor = 0,
	resists = {38,20,0,-1,-1,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 320,
	hideType = "hide_leathery",
	hideAmount = 340,
	boneType = "bone_mammal",
	boneAmount = 320,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/bolma.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bolma_male, "bolma_male")