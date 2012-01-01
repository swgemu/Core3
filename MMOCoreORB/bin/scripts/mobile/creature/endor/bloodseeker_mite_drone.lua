bloodseeker_mite_drone = Creature:new {
	objectName = "@mob/creature_names:bloodseeker_mite_drone",
	socialGroup = "Bloodseeker",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.32,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1609,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {-1,35,-1,45,-1,45,45,-1,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bloodseeker_mite.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(bloodseeker_mite_drone, "bloodseeker_mite_drone")