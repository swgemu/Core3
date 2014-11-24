enraged_reptilian_flier = Creature:new {
	objectName = "@mob/creature_names:enraged_reptilian_flier",
	socialGroup = "reptilian_flier",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.35,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2730,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {125,130,-1,150,150,-1,150,-1,-1},
	meatType = "meat_avian",
	meatAmount = 135,
	hideType = "hide_leathery",
	hideAmount = 90,
	boneType = "bone_avian",
	boneAmount = 85,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 7,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/reptilian_flier_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/pet_control.iff",
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enraged_reptilian_flier, "enraged_reptilian_flier")
