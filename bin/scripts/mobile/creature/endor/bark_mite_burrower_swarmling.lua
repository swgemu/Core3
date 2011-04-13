bark_mite_burrower_swarmling = Creature:new {
	objectName = "@mob/creature_names:bark_mite_burrower_swarmling",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.320000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1609,
	baseHAM = 3900,
	baseHAMmax = 3900,
	armor = 0,
	resists = {0,20,-1,35,-1,20,35,-1,-1},
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
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(bark_mite_burrower_swarmling, "bark_mite_burrower_swarmling")