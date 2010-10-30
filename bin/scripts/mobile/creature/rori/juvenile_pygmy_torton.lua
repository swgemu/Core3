juvenile_pygmy_torton = Creature:new {
	objectName = "@mob/creature_names:torton_pygmy_juvenile",
	socialGroup = "Torton",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.280000,
	damageMin = 150,
	damageMax = 160,
	baseXp = 514,
	baseHAM = 450,
	baseHAMmax = 450,
	armor = 0,
	resists = {20,20,0,0,0,0,0,35,-1},
	meatType = "meat_carnivore",
	meatAmount = 400,
	hideType = "hide_wooly",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 400,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/torton.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(juvenile_pygmy_torton, "juvenile_pygmy_torton")