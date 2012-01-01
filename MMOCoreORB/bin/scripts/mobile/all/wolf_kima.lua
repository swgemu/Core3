wolf_kima = Creature:new {
	objectName = "@mob/creature_names:wolf_kima",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.32,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1426,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "meat_herbivore",
	meatAmount = 10,
	hideType = "hide_bristley",
	hideAmount = 11,
	boneType = "bone_mammal",
	boneAmount = 10,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 0,
	diet = CARNIVORE,

	templates = {"object/mobile/kima.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(wolf_kima, "wolf_kima")