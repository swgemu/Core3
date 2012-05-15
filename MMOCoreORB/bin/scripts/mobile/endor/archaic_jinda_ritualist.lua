archaic_jinda_ritualist = Creature:new {
	objectName = "@mob/creature_names:archaic_jinda_ritualist",
	socialGroup = "Jinda Tribe",
	pvpFaction = "Jinda Tribe",
	faction = "",
	level = 41,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4006,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {30,50,-1,30,30,70,30,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/jinda_male.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(archaic_jinda_ritualist, "archaic_jinda_ritualist")