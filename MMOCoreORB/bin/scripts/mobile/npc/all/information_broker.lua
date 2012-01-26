information_broker = Creature:new {
	objectName = "@mob/creature_names:bothan_information_broker",
	socialGroup = "Mercenary",
	pvpFaction = "",
	faction = "",
	level = 5,
	chanceHit = 0.25,
	damageMin = 45,
	damageMax = 50,
	baseXp = 85,
	baseHAM = 135,
	baseHAMmax = 165,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"rebel_weapons_light"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(information_broker, "information_broker")