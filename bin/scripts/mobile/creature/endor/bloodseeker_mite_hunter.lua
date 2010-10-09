bloodseeker_mite_hunter = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:bloodseeker_mite_hunter",
	socialGroup = "Bloodseeker",
	pvpFaction = "",
	faction = "",
	level = 31,
	chanceHit = 0.360000,
	damageMin = 315,
	damageMax = 340,
	range = 25,
	baseXp = 3097,
	baseHAM = 6550,
	armor = 0,
	resists = {15,45,-1,80,-1,80,80,0,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "hide_scale",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bloodseeker_mite_hunter, "bloodseeker_mite_hunter")
