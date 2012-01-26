imperial_exterminator = Creature:new {
	objectName = "@mob/creature_names:imperial_exterminator",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 28,
	chanceHit = 0.37,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2914,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 2,
	resists = {5,5,5,-1,30,-1,30,-1,-1},
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

	templates = {"object/mobile/dressed_imperial_exterminator.iff"},
	lootgroups = {},
	weapons = {"imperial_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(imperial_exterminator, "imperial_exterminator")