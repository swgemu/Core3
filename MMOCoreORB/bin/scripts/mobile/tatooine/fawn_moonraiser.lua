fawn_moonraiser = Creature:new {
	objectName = "@mob/creature_names:fawn_moonraiser",
	socialGroup = "darklighter",
	faction = "",
	level = 99,
	chanceHit = 0.99,
	damageMin = 640,
	damageMax = 990,
	baseXp = 9243,
	baseHAM = 24000,
	baseHAMmax = 29000,
	armor = 0,
	resists = {40,40,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_fawn_moonraiser.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(fawn_moonraiser, "fawn_moonraiser")
