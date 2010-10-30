domesticated_merek = Creature:new {
	objectName = "@mob/creature_names:domesticated_merek",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 49,
	chanceHit = 0.500000,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4734,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {60,-1,0,80,40,0,40,0,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/merek.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(domesticated_merek, "domesticated_merek")