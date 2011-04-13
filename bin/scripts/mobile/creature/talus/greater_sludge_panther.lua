greater_sludge_panther = Creature:new {
	objectName = "@mob/creature_names:greater_sludge_panther",
	socialGroup = "Sludge Panther",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.350000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2637,
	baseHAM = 8000,
	baseHAMmax = 8000,
	armor = 0,
	resists = {35,0,0,-1,-1,-1,45,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 80,
	hideType = "hide_leathery",
	hideAmount = 70,
	boneType = "bone_mammal",
	boneAmount = 70,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/greater_sludge_panther.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(greater_sludge_panther, "greater_sludge_panther")