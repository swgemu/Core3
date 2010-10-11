elder_gronda = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:gronda_elder",
	socialGroup = "Gronda",
	pvpFaction = "",
	faction = "",
	level = 33,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	range = 0,
	baseXp = 3370,
	baseHAM = 9300,
	armor = 0,
	resists = {60,0,80,0,0,0,-1,25,-1},
	meatType = "meat_carnivore",
	meatAmount = 360,
	hideType = "hide_leathery",
	hideAmount = 270,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(elder_gronda, "elder_gronda")
