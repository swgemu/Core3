rancid_remmer_warrior = Creature:new {
	objectName = "@mob/creature_names:rancid_remmer_warrior",
	socialGroup = "Remmer",
	pvpFaction = "",
	faction = "",
	level = 33,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3279,
	baseHAM = 9300,
	baseHAMmax = 9300,
	armor = 0,
	resists = {60,0,70,0,0,-1,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_bristley",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/remmer.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_red"},
	attacks = {
		{"stunattack","stunChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rancid_remmer_warrior, "rancid_remmer_warrior")