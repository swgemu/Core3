elder_snorbal_female = Creature:new {
	objectName = "@mob/creature_names:elder_snorbal_female",
	socialGroup = "Snorbal",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.410000,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3370,
	baseHAM = 9800,
	baseHAMmax = 9800,
	armor = 0,
	resists = {0,0,0,-1,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 570,
	hideType = "hide_leathery",
	hideAmount = 455,
	boneType = "bone_mammal",
	boneAmount = 420,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/elder_snorbal_female.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(elder_snorbal_female, "elder_snorbal_female")