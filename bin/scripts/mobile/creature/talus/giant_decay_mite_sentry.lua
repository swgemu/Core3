giant_decay_mite_sentry = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:giant_decay_mite_sentry",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.310000,
	damageMin = 160,
	damageMax = 170,
	range = 25,
	baseXp = 1257,
	baseHAM = 3200,
	armor = 0,
	resists = {20,20,-1,0,0,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "hide_",
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
		{"knockdownattack","knockdownChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_decay_mite_sentry, "giant_decay_mite_sentry")
