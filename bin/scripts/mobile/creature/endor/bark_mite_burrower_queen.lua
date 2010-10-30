bark_mite_burrower_queen = Creature:new {
	objectName = "@mob/creature_names:bark_mite_burrower_queen",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 60,
	chanceHit = 0.550000,
	damageMin = 440,
	damageMax = 590,
	baseXp = 5830,
	baseHAM = 12000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {60,50,-1,80,-1,80,80,0,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite_burrower_queen.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"stunattack","stunChance=50"},
		{"strongdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(bark_mite_burrower_queen, "bark_mite_burrower_queen")