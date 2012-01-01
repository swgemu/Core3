hutt_expeditonary_force_leader = Creature:new {
	objectName = "@mob/creature_names:Hutt Expeditonary Force leader",
	socialGroup = "Hutt",
	pvpFaction = "Hutt",
	faction = "",
	level = 21,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2006,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {0,0,0,30,-1,-1,-1,-1,-1},
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
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(hutt_expeditonary_force_leader, "hutt_expeditonary_force_leader")