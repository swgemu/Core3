cowardly_gurreck = Creature:new {
	objectName = "@mob/creature_names:cowardly_gurreck",
	socialGroup = "gurreck",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.31,
	damageMin = 150,
	damageMax = 160,
	baseXp = 831,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {10,25,25,-1,-1,25,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gurreck_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(cowardly_gurreck, "cowardly_gurreck")