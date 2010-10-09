fierce_borgle = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:fierce_borgle",
	socialGroup = "Borgle",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.370000,
	damageMin = 310,
	damageMax = 330,
	range = 0,
	baseXp = 3279,
	baseHAM = 7000,
	armor = 0,
	resists = {40,30,30,-1,75,75,100,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 5,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(fierce_borgle, "fierce_borgle")
