bordok_herd_master = Creature:new {
	objectName = "@mob/creature_names:bordok_herd_master",
	socialGroup = "bordok",
	faction = "",
	level = 40,
	chanceHit = 0.43,
	damageMin = 355,
	damageMax = 420,
	baseXp = 3915,
	baseHAM = 9500,
	baseHAMmax = 11600,
	armor = 0,
	resists = {25,25,25,200,200,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 250,
	hideType = "hide_leathery",
	hideAmount = 175,
	boneType = "bone_mammal",
	boneAmount = 165,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/bordok_hue.iff"},
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(bordok_herd_master, "bordok_herd_master")
