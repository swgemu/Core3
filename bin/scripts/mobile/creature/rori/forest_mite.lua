forest_mite = Creature:new {
	objectName = "@mob/creature_names:forest_mite",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.300000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 714,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 5,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/forest_mite.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(forest_mite, "forest_mite")