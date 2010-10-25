poisonous_krevol_queen = Creature:new {
	objectName = "@mob/creature_names:poisonous_krevol_queen",
	socialGroup = "Krevol",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.300000,
	damageMin = 170,
	damageMax = 180,
	range = 25,
	baseXp = 960,
	baseHAM = 1700,
	armor = 0,
	resists = {25,0,0,-1,20,0,20,-1,-1},
	meatType = "meat_insect",
	meatAmount = 12,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(poisonous_krevol_queen, "poisonous_krevol_queen")
