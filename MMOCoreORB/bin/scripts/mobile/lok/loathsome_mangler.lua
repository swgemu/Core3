loathsome_mangler = Creature:new {
	objectName = "@mob/creature_names:gurk_loathsome_mangler",
	socialGroup = "gurk",
	faction = "",
	level = 33,
	chanceHit = 0.4,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3370,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {120,120,-1,0,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 350,
	hideType = "hide_leathery",
	hideAmount = 276,
	boneType = "bone_mammal",
	boneAmount = 301,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gurk_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/gurk_hue.iff",
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(loathsome_mangler, "loathsome_mangler")
