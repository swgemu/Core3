large_rock_beetle = Creature:new {
	objectName = "@mob/creature_names:large_rock_beetle",
	socialGroup = "Rock Beetle",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.33,
	damageMin = 170,
	damageMax = 180,
	baseXp = 2006,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {20,20,5,15,5,-1,5,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "hide_scaley",
	hideAmount = 14,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 4,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/rock_beetle.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(large_rock_beetle, "large_rock_beetle")