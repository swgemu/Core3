dwarf_gronda = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:dwarf_gronda",
	socialGroup = "Gronda",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.290000,
	damageMin = 130,
	damageMax = 140,
	range = 0,
	baseXp = 514,
	baseHAM = 1300,
	armor = 0,
	resists = {20,20,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 280,
	hideType = "hide_leathery",
	hideAmount = 170,
	boneType = "bone_mammal",
	boneAmount = 90,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(dwarf_gronda, "dwarf_gronda")
