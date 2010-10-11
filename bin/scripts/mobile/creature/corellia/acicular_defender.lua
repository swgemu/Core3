acicular_defender = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:paralope_acicular_defender",
	socialGroup = "Paralope",
	pvpFaction = "",
	faction = "",
	level = 8,
	chanceHit = 0.270000,
	damageMin = 70,
	damageMax = 75,
	range = 0,
	baseXp = 235,
	baseHAM = 450,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 5,
	hideType = "hide_wooly",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.500000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(acicular_defender, "acicular_defender")
