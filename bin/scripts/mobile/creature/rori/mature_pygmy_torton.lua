mature_pygmy_torton = Creature:new {
	objectName = "@mob/creature_names:torton_pygmy_mature",
	socialGroup = "Torton",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.350000,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2730,
	baseHAM = 5550,
	baseHAMmax = 5550,
	armor = 0,
	resists = {35,35,0,0,-1,-1,-1,60,-1},
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
		{"stunattack","stunChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mature_pygmy_torton, "mature_pygmy_torton")