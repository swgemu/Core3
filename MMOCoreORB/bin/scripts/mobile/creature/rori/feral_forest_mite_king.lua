feral_forest_mite_king = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:feral_forest_mite_king",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.350000,
	damageMin = 230,
	damageMax = 240,
	range = 25,
	baseXp = 2822,
	baseHAM = 7550,
	armor = 0,
	resists = {0,40,-1,50,-1,50,50,-1,-1},
	meatType = "meat_insect",
	meatAmount = 20,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(feral_forest_mite_king, "feral_forest_mite_king")
