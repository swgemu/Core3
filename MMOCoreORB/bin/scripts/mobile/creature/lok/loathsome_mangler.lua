loathsome_mangler = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:gurk_loathsome_mangler",
	socialGroup = "Gurk",
	pvpFaction = "",
	faction = "",
	level = 33,
	chanceHit = 0.400000,
	damageMin = 335,
	damageMax = 380,
	range = 0,
	baseXp = 3370,
	baseHAM = 9100,
	armor = 0,
	resists = {20,20,-1,0,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 350,
	hideType = "hide_leathery",
	hideAmount = 276,
	boneType = "bone_mammal",
	boneAmount = 301,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(loathsome_mangler, "loathsome_mangler")
