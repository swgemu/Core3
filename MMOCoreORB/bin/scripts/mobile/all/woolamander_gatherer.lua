woolamander_gatherer = Creature:new {
	objectName = "@mob/creature_names:woolamander_gatherer",
	socialGroup = "woolamander",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.38,
	damageMin = 280,
	damageMax = 290,
	baseXp = 2822,
	baseHAM = 8300,
	baseHAMmax = 10100,
	armor = 1,
	resists = {20,20,0,80,80,80,0,0,0},
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
	optionsBitmask = 0,
	diet = HERBIVORE,

	templates = {"object/mobile/woolamander.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(woolamander_gatherer, "woolamander_gatherer")