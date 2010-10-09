foul_desecrator = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:kamurith_foul_desecrator",
	socialGroup = "Kamurith",
	pvpFaction = "",
	faction = "",
	level = 60,
	chanceHit = 0.550000,
	damageMin = 470,
	damageMax = 650,
	range = 0,
	baseXp = 5830,
	baseHAM = 12500,
	armor = 0,
	resists = {25,0,0,0,0,0,20,20,-1},
	meatType = "meat_carnivore",
	meatAmount = 90,
	hideType = "hide_leathery",
	hideAmount = 65,
	boneType = "bone_avian",
	boneAmount = 50,
	milk = 0.000000,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"strongdisease",""},
		{"creatureareadisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(foul_desecrator, "foul_desecrator")
