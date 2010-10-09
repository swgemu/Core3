Kinn_Dray = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "Kinn`Dray",
	socialGroup = "Gap. Recluse",
	pvpFaction = "",
	faction = "",
	level = 126,
	chanceHit = 4.750000,
	damageMin = 830,
	damageMax = 1370,
	range = 25,
	baseXp = 11953,
	baseHAM = 45500,
	armor = 0,
	resists = {55,55,35,30,30,30,0,30,-1},
	meatType = "meat_insect",
	meatAmount = 11,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"creatureareapoison",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(Kinn_Dray, "Kinn_Dray")
