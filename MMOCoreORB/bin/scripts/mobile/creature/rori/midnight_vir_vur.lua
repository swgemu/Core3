midnight_vir_vur = Creature:new {
	objectName = "@mob/creature_names:midnight_vir_vur",
	socialGroup = "Vir Vur",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 960,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {5,5,5,5,5,5,5,-1,-1},
	meatType = "meat_avian",
	meatAmount = 10,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 5,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/vir_vur.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(midnight_vir_vur, "midnight_vir_vur")