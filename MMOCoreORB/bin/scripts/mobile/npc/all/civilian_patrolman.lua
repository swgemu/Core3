civilian_patrolman = Creature:new {
	objectName = "@mob/creature_names:imperial_civil_patrolman",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 6,
	chanceHit = 0.25,
	damageMin = 50,
	damageMax = 55,
	baseXp = 147,
	baseHAM = 180,
	baseHAMmax = 220,
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"imperial_weapons_light"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(civilian_patrolman, "civilian_patrolman")