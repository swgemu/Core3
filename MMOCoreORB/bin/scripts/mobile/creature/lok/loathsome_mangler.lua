loathsome_mangler = Creature:new {
	objectName = "@mob/creature_names:gurk_loathsome_mangler",
	socialGroup = "Gurk",
	pvpFaction = "",
	faction = "",
	level = 33,
	chanceHit = 0.4,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3370,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {20,20,-1,0,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 350,
	hideType = "hide_leathery",
	hideAmount = 276,
	boneType = "bone_mammal",
	boneAmount = 301,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gurk.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(loathsome_mangler, "loathsome_mangler")