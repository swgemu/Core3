verne = Creature:new {
	objectName = "@mob/creature_names:verne",
	socialGroup = "Verne",
	pvpFaction = "",
	faction = "",
	level = 0,
	chanceHit = 0,
	damageMin = 0,
	damageMax = 0,
	baseXp = 0,
	baseHAM = 0,
	baseHAMmax = 0,
	armor = 0,
	resists = {5,5,5,-1,-1,25,25,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 125,
	hideType = "hide_leathery",
	hideAmount = 90,
	boneType = "bone_mammal",
	boneAmount = 80,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 0,
	diet = HERBIVORE,

	templates = {"object/mobile/verne.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(verne, "verne")