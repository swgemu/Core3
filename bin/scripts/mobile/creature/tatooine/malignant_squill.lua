malignant_squill = Creature:new {
	objectName = "@mob/creature_names:malignant_squill",
	socialGroup = "Squill",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.500000,
	damageMin = 420,
	damageMax = 550,
	baseXp = 4916,
	baseHAM = 10300,
	baseHAMmax = 10300,
	armor = 0,
	resists = {0,0,10,0,100,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 25,
	hideType = "hide_leathery",
	hideAmount = 25,
	boneType = "bone_mammal",
	boneAmount = 20,
	milk = 0,
	tamingChance = 0.100000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/squill.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"strongdisease",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(malignant_squill, "malignant_squill")