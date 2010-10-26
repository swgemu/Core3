savage_quenker = Creature:new {
	objectName = "@mob/creature_names:savage_quenker",
	socialGroup = "Quenker",
	pvpFaction = "",
	faction = "",
	level = 28,
	chanceHit = 0.360000,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2822,
	baseHAM = 7550,
	armor = 0,
	resists = {35,35,0,0,-1,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_scaley",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(savage_quenker, "savage_quenker")
