giant_cave_veermok = Creature:new {
	objectName = "@mob/creature_names:veermok_giant_cave",
	socialGroup = "Veermok",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.350000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2730,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {50,50,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 150,
	hideType = "hide_bristley",
	hideAmount = 150,
	boneType = "bone_mammal",
	boneAmount = 60,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_veermok.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_cave_veermok, "giant_cave_veermok")