weathered_jinda_shaman = Creature:new {
	objectName = "@mob/creature_names:weathered_jinda_shaman",
	socialGroup = "Jinda Tribe",
	pvpFaction = "Jinda Tribe",
	faction = "",
	level = 35,
	chanceHit = 0.410000,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3460,
	baseHAM = 8600,
	baseHAMmax = 10500,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(weathered_jinda_shaman, "weathered_jinda_shaman")