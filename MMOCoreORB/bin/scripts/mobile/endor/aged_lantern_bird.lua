aged_lantern_bird = Creature:new {
	objectName = "@mob/creature_names:aged_lantern_bird",
	socialGroup = "lantern",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2730,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {15,155,-1,15,15,15,-1,15,-1},
	meatType = "meat_herbivore",
	meatAmount = 75,
	hideType = "hide_leathery",
	hideAmount = 41,
	boneType = "bone_avian",
	boneAmount = 46,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/lantern_bird_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/lantern_bird_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(aged_lantern_bird, "aged_lantern_bird")
