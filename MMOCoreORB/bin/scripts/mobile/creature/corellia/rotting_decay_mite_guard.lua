rotting_decay_mite_guard = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:rotting_pustule_guard",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.300000,
	damageMin = 140,
	damageMax = 150,
	range = 0,
	baseXp = 714,
	baseHAM = 1300,
	armor = 0,
	resists = {0,0,0,0,0,0,10,-1,-1},
	meatType = "meat_insect",
	meatAmount = 9,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(rotting_decay_mite_guard, "rotting_decay_mite_guard")
