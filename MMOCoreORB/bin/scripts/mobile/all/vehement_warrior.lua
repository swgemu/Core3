vehement_warrior = Creature:new {
	objectName = "@mob/creature_names:vehement_warrior",
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
	resists = {10,5,0,0,0,0,0,0,-1},
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

	aiTemplate = "default",

	templates = {"object/mobile/durni.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(vehement_warrior, "vehement_warrior")