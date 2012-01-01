dantari_chief = Creature:new {
	objectName = "@mob/creature_names:Dantari_chief",
	socialGroup = "Dantari Raider",
	pvpFaction = "Dantari Raider",
	faction = "",
	level = 42,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4188,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {35,50,50,-1,70,70,-1,0,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(dantari_chief, "dantari_chief")