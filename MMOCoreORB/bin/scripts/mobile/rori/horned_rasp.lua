horned_rasp = Creature:new {
	objectName = "@mob/creature_names:horned_rasp",
	socialGroup = "rasp",
	pvpFaction = "",
	faction = "",
	level = 6,
	chanceHit = 0.25,
	damageMin = 50,
	damageMax = 55,
	baseXp = 147,
	baseHAM = 180,
	baseHAMmax = 220,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 8,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 1,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/horned_rasp.iff"},
	controlDeviceTemplate = "object/intangible/pet/horned_rasp_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(horned_rasp, "horned_rasp")
