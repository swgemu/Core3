bloodseeker_mite_drone = Creature:new {
	objectName = "@mob/creature_names:bloodseeker_mite_drone",
	socialGroup = "bloodseeker",
	faction = "",
	level = 20,
	chanceHit = 0.32,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1609,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {-1,135,-1,145,-1,145,145,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
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

	templates = {"object/mobile/bloodseeker_mite.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	scale = 0.9,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(bloodseeker_mite_drone, "bloodseeker_mite_drone")
