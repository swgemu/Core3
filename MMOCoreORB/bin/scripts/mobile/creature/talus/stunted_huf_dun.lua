stunted_huf_dun = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:stunted_huf_dun",
	socialGroup = "Huf Dun",
	pvpFaction = "",
	faction = "",
	level = 9,
	chanceHit = 0.270000,
	damageMin = 90,
	damageMax = 110,
	range = 0,
	baseXp = 235,
	baseHAM = 750,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 775,
	hideType = "hide_leathery",
	hideAmount = 800,
	boneType = "bone_mammal",
	boneAmount = 775,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(stunted_huf_dun, "stunted_huf_dun")
