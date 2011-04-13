frenzied_fynock_guardian = Creature:new {
	objectName = "@mob/creature_names:frenzied_fynock_guardian",
	socialGroup = "Fynock",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.290000,
	damageMin = 150,
	damageMax = 160,
	baseXp = 514,
	baseHAM = 900,
	baseHAMmax = 900,
	armor = 0,
	resists = {0,0,10,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 8,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 8,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/fynock.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(frenzied_fynock_guardian, "frenzied_fynock_guardian")