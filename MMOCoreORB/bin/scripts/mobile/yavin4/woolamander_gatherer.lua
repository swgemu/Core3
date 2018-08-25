woolamander_gatherer = Creature:new {
	objectName = "@mob/creature_names:woolamander_gatherer",
	socialGroup = "woolamander",
	faction = "",
	level = 29,
	chanceHit = 0.38,
	damageMin = 280,
	damageMax = 290,
	baseXp = 2822,
	baseHAM = 8300,
	baseHAMmax = 10100,
	armor = 0,
	resists = {15,15,-1,180,180,180,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 20,
	hideType = "hide_wooly",
	hideAmount = 20,
	boneType = "bone_mammal",
	boneAmount = 20,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD + STALKER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/woolamander_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = 1.05,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""},
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(woolamander_gatherer, "woolamander_gatherer")
