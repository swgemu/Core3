male_plains_tusk_cat = Creature:new {
	objectName = "@mob/creature_names:male_great_grass_plains_tusk_cat",
	socialGroup = "Tusk Cat",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.310000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 960,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {0,0,0,35,35,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 75,
	hideType = "hide_bristley",
	hideAmount = 45,
	boneType = "bone_mammal",
	boneAmount = 40,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + STALKER,
	diet = CARNIVORE,

	templates = {"object/mobile/tusk_cat.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(male_plains_tusk_cat, "male_plains_tusk_cat")