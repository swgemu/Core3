female_squall = Creature:new {
	objectName = "@mob/creature_names:squall_female",
	socialGroup = "squall",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 8,
	hideType = "hide_bristley",
	hideAmount = 12,
	boneType = "bone_mammal",
	boneAmount = 8,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/squall_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/squall_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(female_squall, "female_squall")
