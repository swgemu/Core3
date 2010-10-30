disturbed_bolma = Creature:new {
	objectName = "@mob/creature_names:disturbed_bolma",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.350000,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2443,
	baseHAM = 6000,
	baseHAMmax = 6000,
	armor = 0,
	resists = {0,30,0,-1,-1,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 160,
	boneType = "bone_mammal",
	boneAmount = 150,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/bolma.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(disturbed_bolma, "disturbed_bolma")