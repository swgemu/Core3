angler_recluse = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:angler_recluse",
	socialGroup = "Angler",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.360000,
	damageMin = 250,
	damageMax = 260,
	range = 0,
	baseXp = 2637,
	baseHAM = 8550,
	armor = 0,
	resists = {25,20,-1,0,0,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 2,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(angler_recluse, "angler_recluse")
