loam_hedge = Creature:new {
	objectName = "@mob/creature_names:loam_redge",
	customName = "Inquisitor Loam Redge",--according to ZAM that's the name
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9429,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/loam_redge.iff"},
	lootGroups = {},
	weapons = {""},
	conversationTemplate = "",
	outfit = "loam_redge_outfit",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(loam_hedge, "loam_hedge")