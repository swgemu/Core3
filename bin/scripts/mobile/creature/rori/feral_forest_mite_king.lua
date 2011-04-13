feral_forest_mite_king = Creature:new {
	objectName = "@mob/creature_names:feral_forest_mite_king",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.350000,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2822,
	baseHAM = 7550,
	baseHAMmax = 7550,
	armor = 0,
	resists = {0,40,-1,50,-1,50,50,-1,-1},
	meatType = "meat_insect",
	meatAmount = 20,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/forest_mite.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"blindattack","blindChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(feral_forest_mite_king, "feral_forest_mite_king")