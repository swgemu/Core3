dantari_strategist = Creature:new {
	objectName = "@mob/creature_names:Dantari_strategist",
	socialGroup = "Dantari Raider",
	pvpFaction = "Dantari Raider",
	faction = "",
	level = 29,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2914,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {0,20,40,-1,50,50,-1,20,-1},
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

	templates = {},
	lootgroups = {},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(dantari_strategist, "dantari_strategist")