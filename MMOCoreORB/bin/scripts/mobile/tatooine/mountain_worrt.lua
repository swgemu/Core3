mountain_worrt = Creature:new {
	objectName = "@mob/creature_names:mountain_worrt",
	socialGroup = "self",
	faction = "",
	level = 22,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 1803,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {10,130,10,135,135,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 4,
	hideType = "hide_leathery",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mountain_worrt.iff"},
	controlDeviceTemplate = "object/intangible/pet/worrt_hue.iff",
	scale = 1.25,
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_worrt, "mountain_worrt")
