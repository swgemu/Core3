acklay = Creature:new {
	objectName = "@mob/creature_names:geonosian_acklay_bunker_boss",
	socialGroup = "Geon. Monster",
	pvpFaction = "",
	faction = "",
	level = 157,
	chanceHit = 9.250000,
	damageMin = 935,
	damageMax = 1580,
	baseXp = 14884,
	baseHAM = 100000,
	baseHAMmax = 100000,
	armor = 0,
	resists = {30,45,55,55,45,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/acklay_hue.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"creatureareacombo",""}
	}
}

CreatureTemplates:addCreatureTemplate(acklay, "acklay")