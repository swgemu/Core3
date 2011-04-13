snorbal_matriarch = Creature:new {
	objectName = "@mob/creature_names:snorbal_matriarch",
	socialGroup = "Snorbal",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.470000,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4370,
	baseHAM = 10800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {35,35,0,-1,-1,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 600,
	hideType = "hide_leathery",
	hideAmount = 475,
	boneType = "bone_mammal",
	boneAmount = 435,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/snorbal_matriarch.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(snorbal_matriarch, "snorbal_matriarch")