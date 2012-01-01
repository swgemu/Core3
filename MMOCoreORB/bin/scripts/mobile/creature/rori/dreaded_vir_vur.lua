dreaded_vir_vur = Creature:new {
	objectName = "@mob/creature_names:dreaded_vir_vir",
	socialGroup = "Vir Vur",
	pvpFaction = "",
	faction = "",
	level = 38,
	chanceHit = 0.44,
	damageMin = 370,
	damageMax = 450,
	baseXp = 3824,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {40,0,-1,-1,0,0,0,0,-1},
	meatType = "meat_avian",
	meatAmount = 25,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 16,
	milk = 0,
	tamingChance = 0.2,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
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

CreatureTemplates:addCreatureTemplate(dreaded_vir_vur, "dreaded_vir_vur")