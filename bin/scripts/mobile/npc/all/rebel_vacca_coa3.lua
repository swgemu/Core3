rebel_vacca_coa3 = Creature:new {
	objectName = "Rebel Vacca (COA3)",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 35,
	chanceHit = 0.410000,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3370,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"rebel_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(rebel_vacca_coa3, "rebel_vacca_coa3")