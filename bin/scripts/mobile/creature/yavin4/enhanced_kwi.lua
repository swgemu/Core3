enhanced_kwi = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:geonosian_enhanced_kwi",
	socialGroup = "Geon. Monster",
	pvpFaction = "",
	faction = "",
	level = 106,
	chanceHit = 1.750000,
	damageMin = 690,
	damageMax = 1090,
	range = 0,
	baseXp = 10081,
	baseHAM = 30000,
	armor = 0,
	resists = {40,40,0,40,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 85,
	boneType = "bone_mammal",
	boneAmount = 75,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = HERBIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enhanced_kwi, "enhanced_kwi")
