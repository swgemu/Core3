vehement_warrior = Creature:new {
	objectName = "@mob/creature_names:durni_vehement_warrior",
	socialGroup = "durni",
	pvpFaction = "",
	faction = "",
	level = 9,
	chanceHit = 0.28,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 625,
	baseHAMmax = 825,
	armor = 0,
	resists = {105,105,0,0,0,0,0,110,-1},
	meatType = "meat_herbivore",
	meatAmount = 5,
	hideType = "hide_wooly",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 0,
	diet = HERBIVORE,

	templates = {"object/mobile/durni.iff"},
	controlDeviceTemplate = "object/intangible/pet/durni_hue.iff",
	scale = 1.25,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(vehement_warrior, "vehement_warrior")
