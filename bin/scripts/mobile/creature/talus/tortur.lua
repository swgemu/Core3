tortur = Creature:new {
	objectName = "@mob/creature_names:tortur",
	socialGroup = "Tortur",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.340000,
	damageMin = 260,
	damageMax = 270,
	baseXp = 1803,
	baseHAM = 3200,
	baseHAMmax = 3200,
	armor = 0,
	resists = {0,0,0,0,-1,-1,-1,45,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "bone_mammal",
	boneAmount = 1000,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/meager_tortur.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(tortur, "tortur")