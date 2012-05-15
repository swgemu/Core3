bark_mite_burrower_swarmling = Creature:new {
	objectName = "@mob/creature_names:bark_mite_burrower_swarmling",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.32,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1609,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {5,20,-1,35,-1,20,35,-1,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(bark_mite_burrower_swarmling, "bark_mite_burrower_swarmling")