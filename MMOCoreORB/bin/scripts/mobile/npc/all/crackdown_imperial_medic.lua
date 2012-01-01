crackdown_imperial_medic = Creature:new {
	objectName = "@mob/creature_names:crackdown_imperial_medic",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 1,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 40,
	baseHAM = 2900,
	baseHAMmax = 3500,
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
	creatureBitmask = PACK + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"imperial_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(crackdown_imperial_medic, "crackdown_imperial_medic")