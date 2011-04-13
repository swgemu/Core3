razor_cat = Creature:new {
	objectName = "@mob/creature_names:bio_engineered_sand_panther",
	socialGroup = "Sand Panther",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.340000,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2006,
	baseHAM = 7000,
	baseHAMmax = 7000,
	armor = 0,
	resists = {0,0,0,60,0,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/corellian_sand_panther.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(razor_cat, "razor_cat")