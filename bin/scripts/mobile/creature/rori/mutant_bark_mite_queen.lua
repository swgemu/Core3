mutant_bark_mite_queen = Creature:new {
	objectName = "@mob/creature_names:mutant_bark_mite_queen",
	socialGroup = "Mut. Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 38,
	chanceHit = 0.390000,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3824,
	baseHAM = 9400,
	baseHAMmax = 9400,
	armor = 0,
	resists = {65,65,0,55,55,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 35,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite_burrower_queen.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"strongpoison",""},
		{"creatureareableeding",""}
	}
}

CreatureTemplates:addCreatureTemplate(mutant_bark_mite_queen, "mutant_bark_mite_queen")