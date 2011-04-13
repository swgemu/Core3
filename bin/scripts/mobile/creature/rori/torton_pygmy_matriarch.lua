torton_pygmy_matriarch = Creature:new {
	objectName = "@mob/creature_names:torton_pygmy_matriarch",
	socialGroup = "Torton",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.360000,
	damageMin = 280,
	damageMax = 290,
	baseXp = 2730,
	baseHAM = 7000,
	baseHAMmax = 7000,
	armor = 0,
	resists = {20,20,0,0,-1,-1,-1,100,-1},
	meatType = "meat_carnivore",
	meatAmount = 700,
	hideType = "hide_wooly",
	hideAmount = 500,
	boneType = "bone_mammal",
	boneAmount = 700,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/torton.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(torton_pygmy_matriarch, "torton_pygmy_matriarch")