bloodseeker_mite_queen = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:bloodseeker_mite_queen",
	socialGroup = "Bloodseeker",
	pvpFaction = "",
	faction = "",
	level = 38,
	chanceHit = 0.410000,
	damageMin = 330,
	damageMax = 370,
	range = 0,
	baseXp = 3824,
	baseHAM = 9800,
	armor = 0,
	resists = {40,45,-1,80,-1,80,80,-1,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "hide_scale",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"strongdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(bloodseeker_mite_queen, "bloodseeker_mite_queen")
