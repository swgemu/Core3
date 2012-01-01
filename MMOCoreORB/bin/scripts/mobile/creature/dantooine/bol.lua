bol = Creature:new {
	objectName = "@mob/creature_names:bol",
	socialGroup = "Bol",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.39,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2914,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {35,20,0,20,20,0,20,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/bol.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bol, "bol")