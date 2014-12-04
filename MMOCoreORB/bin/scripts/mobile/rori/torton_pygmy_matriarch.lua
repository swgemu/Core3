torton_pygmy_matriarch = Creature:new {
	objectName = "@mob/creature_names:torton_pygmy_matriarch",
	socialGroup = "torton",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.36,
	damageMin = 280,
	damageMax = 290,
	baseXp = 2730,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {120,120,15,15,-1,-1,-1,200,-1},
	meatType = "meat_carnivore",
	meatAmount = 700,
	hideType = "hide_wooly",
	hideAmount = 500,
	boneType = "bone_mammal",
	boneAmount = 700,
	milk = 0,
	tamingChance = 0,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/torton_hue.iff"},
	scale = .6,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(torton_pygmy_matriarch, "torton_pygmy_matriarch")
