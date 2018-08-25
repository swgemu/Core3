bark_mite_burrower_drone = Creature:new {
	objectName = "@mob/creature_names:bark_mite_burrower_drone",
	socialGroup = "mite",
	faction = "",
	level = 29,
	chanceHit = 0.36,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2914,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {135,120,-1,170,-1,160,170,15,-1},
	meatType = "meat_insect",
	meatAmount = 50,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	scale = 0.9,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(bark_mite_burrower_drone, "bark_mite_burrower_drone")
