poisonous_krevol_queen = Creature:new {
	objectName = "@mob/creature_names:poisonous_krevol_queen",
	socialGroup = "Krevol",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.300000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 960,
	baseHAM = 1700,
	baseHAMmax = 1700,
	armor = 0,
	resists = {25,0,0,-1,20,0,20,-1,-1},
	meatType = "meat_insect",
	meatAmount = 12,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/poisonous_krevol_queen.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	attacks = {
		{"blindattack","blindChance=50"},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(poisonous_krevol_queen, "poisonous_krevol_queen")