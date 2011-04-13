vicious_korga_battlelord = Creature:new {
	objectName = "@mob/creature_names:vicious_korga_battlelord",
	socialGroup = "Korga Tribe",
	pvpFaction = "Korga Tribe",
	faction = "",
	level = 48,
	chanceHit = 0.490000,
	damageMin = 410,
	damageMax = 530,
	baseXp = 4734,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 0,
	resists = {25,10,0,50,50,-1,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(vicious_korga_battlelord, "vicious_korga_battlelord")