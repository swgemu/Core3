diseased_blurrg = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:diseased_blurrg",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 37,
	chanceHit = 0.410000,
	damageMin = 320,
	damageMax = 350,
	range = 0,
	baseXp = 3551,
	baseHAM = 9800,
	armor = 0,
	resists = {40,40,-1,50,50,0,50,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = NONE,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"mediumdisease",""},
		{"creatureareableeding",""}
	}
}

CreatureTemplates:addCreatureTemplate(diseased_blurrg, "diseased_blurrg")
