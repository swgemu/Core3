crazed_gurk_destroyer = Creature:new {
	objectName = "@mob/creature_names:crazed_gurk_destroyer",
	socialGroup = "Gurk",
	pvpFaction = "",
	faction = "",
	level = 43,
	chanceHit = 0.44,
	damageMin = 385,
	damageMax = 480,
	baseXp = 4279,
	baseHAM = 9600,
	baseHAMmax = 11800,
	armor = 0,
	resists = {30,30,30,30,30,30,30,30,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 275,
	boneType = "bone_mammal",
	boneAmount = 300,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gurk.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(crazed_gurk_destroyer, "crazed_gurk_destroyer")