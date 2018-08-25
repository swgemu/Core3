shimmering_lantern_bird = Creature:new {
	objectName = "@mob/creature_names:shimmering_lantern_bird",
	socialGroup = "lantern",
	faction = "",
	level = 30,
	chanceHit = 0.37,
	damageMin = 270,
	damageMax = 280,
	baseXp = 3005,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {130,145,15,-1,15,-1,-1,15,-1},
	meatType = "meat_herbivore",
	meatAmount = 75,
	hideType = "hide_leathery",
	hideAmount = 41,
	boneType = "bone_avian",
	boneAmount = 46,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/lantern_bird_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 1.05,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(shimmering_lantern_bird, "shimmering_lantern_bird")
