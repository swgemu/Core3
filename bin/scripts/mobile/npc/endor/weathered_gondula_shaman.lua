weathered_gondula_shaman = Creature:new {
	objectName = "@mob/creature_names:weathered_gondula_shaman",
	socialGroup = "Condula Tribe",
	pvpFaction = "Condula Tribe",
	faction = "",
	level = 43,
	chanceHit = 0.450000,
	damageMin = 350,
	damageMax = 410,
	baseXp = 4188,
	baseHAM = 9400,
	baseHAMmax = 11400,
	armor = 0,
	resists = {40,40,0,0,60,60,0,0,-1},
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
	weapons = {"ewok_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(weathered_gondula_shaman, "weathered_gondula_shaman")