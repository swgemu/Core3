lantern_bird = Creature:new {
	objectName = "@mob/creature_names:lantern_bird",
	socialGroup = "lantern",
	faction = "",
	level = 21,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {10,130,10,-1,10,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 46,
	hideType = "hide_leathery",
	hideAmount = 41,
	boneType = "bone_avian",
	boneAmount = 46,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/lantern_bird_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/lantern_bird_hue.iff",
	scale = 0.9,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(lantern_bird, "lantern_bird")
