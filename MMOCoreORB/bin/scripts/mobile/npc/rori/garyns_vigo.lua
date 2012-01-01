garyns_vigo = Creature:new {
	objectName = "@mob/creature_names:Garyn's vigo",
	socialGroup = "Garyn",
	pvpFaction = "Garyn",
	faction = "",
	level = 32,
	chanceHit = 0.4,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3279,
	baseHAM = 8600,
	baseHAMmax = 10500,
	armor = 0,
	resists = {25,25,0,0,-1,0,0,-1,-1},
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
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(garyns_vigo, "garyns_vigo")