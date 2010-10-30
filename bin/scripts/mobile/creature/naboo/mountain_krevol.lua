mountain_krevol = Creature:new {
	objectName = "@mob/creature_names:mountain_krevol",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.390000,
	damageMin = 150,
	damageMax = 160,
	baseXp = 831,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {15,5,0,35,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 3,
	hideType = "hide_scaley",
	hideAmount = 2,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/horned_krevol.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_krevol, "mountain_krevol")