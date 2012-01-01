elite_novatrooper_commander = Creature:new {
	objectName = "@mob/creature_names:Elite_Novatrooper_Commander",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 201,
	chanceHit = 16,
	damageMin = 1145,
	damageMax = 2000,
	baseXp = 19104,
	baseHAM = 160000,
	baseHAMmax = 195000,
	armor = 0,
	resists = {60,75,80,30,0,0,30,45,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"stormtrooper_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(elite_novatrooper_commander, "elite_novatrooper_commander")