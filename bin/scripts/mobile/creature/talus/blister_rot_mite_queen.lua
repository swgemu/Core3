blister_rot_mite_queen = Creature:new {
	objectName = "@mob/creature_names:blister_rot_queen",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.300000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 960,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {0,0,0,0,10,0,10,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
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

	templates = {"object/mobile/blister_rot_queen.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_red"},
	attacks = {
		{"mediumdisease",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blister_rot_mite_queen, "blister_rot_mite_queen")