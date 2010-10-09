enraged_dune_kimogila = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:enraged_dune_kimogila",
	socialGroup = "Kimogila",
	pvpFaction = "",
	faction = "",
	level = 148,
	chanceHit = 6.250000,
	damageMin = 940,
	damageMax = 1590,
	range = 0,
	baseXp = 14030,
	baseHAM = 68500,
	armor = 0,
	resists = {80,90,80,100,80,80,100,80,-1},
	meatType = "meat_carnivore",
	meatAmount = 1600,
	hideType = "hide_leathery",
	hideAmount = 1450,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"creatureareaattack",""},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enraged_dune_kimogila, "enraged_dune_kimogila")
