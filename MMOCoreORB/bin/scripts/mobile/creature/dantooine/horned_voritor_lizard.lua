horned_voritor_lizard = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:horned_voritor_jungle_lizard",
	socialGroup = "Voritor Lizard",
	pvpFaction = "",
	faction = "",
	level = 53,
	chanceHit = 0.500000,
	damageMin = 395,
	damageMax = 500,
	range = 0,
	baseXp = 5099,
	baseHAM = 11000,
	armor = 0,
	resists = {40,40,0,0,80,80,80,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_leathery",
	hideAmount = 40,
	boneType = "bone_avian",
	boneAmount = 50,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"strongpoison",""},
		{"creatureareapoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(horned_voritor_lizard, "horned_voritor_lizard")
