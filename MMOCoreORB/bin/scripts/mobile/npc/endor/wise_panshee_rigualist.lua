wise_panshee_rigualist = Creature:new {
	objectName = "@mob/creature_names:wise_Panshee_rigualist",
	socialGroup = "Panshee Tribe",
	pvpFaction = "Panshee Tribe",
	faction = "",
	level = 51,
	chanceHit = 0.5,
	damageMin = 410,
	damageMax = 530,
	baseXp = 4916,
	baseHAM = 9900,
	baseHAMmax = 12100,
	armor = 0,
	resists = {15,15,15,60,60,60,60,-1,-1},
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

	templates = {"object/mobile/ewok_male.iff"},
	lootgroups = {},
	weapons = {"ewok_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(wise_panshee_rigualist, "wise_panshee_rigualist")