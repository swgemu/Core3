monstrous_brute = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:rancor_monstrous_brute",
	socialGroup = "Rancor",
	pvpFaction = "",
	faction = "",
	level = 87,
	chanceHit = 0.820000,
	damageMin = 595,
	damageMax = 900,
	range = 0,
	baseXp = 8315,
	baseHAM = 14500,
	armor = 0,
	resists = {0,60,0,100,100,100,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 878,
	boneType = "bone_mammal",
	boneAmount = 778,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"creatureareaattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(monstrous_brute, "monstrous_brute")
