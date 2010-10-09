arachne_queen = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:queen_arachne",
	socialGroup = "Arachne",
	pvpFaction = "",
	faction = "",
	level = 63,
	chanceHit = 0.600000,
	damageMin = 445,
	damageMax = 600,
	range = 0,
	baseXp = 6105,
	baseHAM = 12500,
	armor = 0,
	resists = {50,35,0,80,80,0,80,-1,-1},
	meatType = "meat_insect",
	meatAmount = 60,
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
		{"creatureareapoison",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(arachne_queen, "arachne_queen")
