gleaming_lantern_bird = Creature:new {
	objectName = "@mob/creature_names:gleaming_lantern_bird",
	socialGroup = "lantern",
	faction = "",
	level = 34,
	chanceHit = 0.4,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3370,
	baseHAM = 8600,
	baseHAMmax = 10600,
	armor = 0,
	resists = {135,145,20,-1,20,20,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 75,
	hideType = "hide_leathery",
	hideAmount = 41,
	boneType = "bone_avian",
	boneAmount = 46,
	milk = 0,
	tamingChance = 0.2,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/lantern_bird_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/lantern_bird_hue.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(gleaming_lantern_bird, "gleaming_lantern_bird")
