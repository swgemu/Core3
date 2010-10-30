thune_herd_leader = Creature:new {
	objectName = "@mob/creature_names:thune_herd_leader",
	socialGroup = "Thune",
	pvpFaction = "",
	faction = "",
	level = 48,
	chanceHit = 0.480000,
	damageMin = 375,
	damageMax = 460,
	baseXp = 4734,
	baseHAM = 10900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {40,60,0,-1,-1,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 135,
	hideType = "hide_wooly",
	hideAmount = 150,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/thune_herd_leader.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(thune_herd_leader, "thune_herd_leader")