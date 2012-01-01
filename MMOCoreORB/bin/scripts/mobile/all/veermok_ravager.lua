veermok_ravager = Creature:new {
	objectName = "@mob/creature_names:veermok_ravager",
	socialGroup = "Veermok",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 960,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {5,5,5,5,5,5,5,0,0},
	meatType = "meat_carnivore",
	meatAmount = 150,
	hideType = "hide_bristley",
	hideAmount = 150,
	boneType = "bone_mammal",
	boneAmount = 60,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 0,
	diet = CARNIVORE,

	templates = {"object/mobile/alpha_veermok.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(veermok_ravager, "veermok_ravager")