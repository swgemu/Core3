gleaming_lantern_bird = Creature:new {
	objectName = "@mob/creature_names:gleaming_lantern_bird",
	socialGroup = "Lantern",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.400000,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3370,
	baseHAM = 9600,
	baseHAMmax = 9600,
	armor = 0,
	resists = {35,45,0,-1,0,0,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 41,
	boneType = "bone_avian",
	boneAmount = 46,
	milk = 0,
	tamingChance = 0.200000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/lantern_bird.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gleaming_lantern_bird, "gleaming_lantern_bird")