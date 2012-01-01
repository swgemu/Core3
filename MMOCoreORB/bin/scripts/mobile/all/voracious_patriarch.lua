voracious_patriarch = Creature:new {
	objectName = "@mob/creature_names:voracious_patriarch",
	socialGroup = "Torton",
	pvpFaction = "",
	faction = "",
	level = 37,
	chanceHit = 0.4,
	damageMin = 365,
	damageMax = 400,
	baseXp = 3642,
	baseHAM = 8500,
	baseHAMmax = 10300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "meat_carnivore",
	meatAmount = 1300,
	hideType = "hide_wooly",
	hideAmount = 1150,
	boneType = "bone_mammal",
	boneAmount = 1300,
	milk = 0,
	tamingChance = 0,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 0,
	diet = CARNIVORE,

	templates = {"object/mobile/torton.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(voracious_patriarch, "voracious_patriarch")