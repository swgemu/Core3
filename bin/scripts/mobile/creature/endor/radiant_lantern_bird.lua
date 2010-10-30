radiant_lantern_bird = Creature:new {
	objectName = "@mob/creature_names:radiant_lantern_bird",
	socialGroup = "Lantern",
	pvpFaction = "",
	faction = "",
	level = 40,
	chanceHit = 0.430000,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3915,
	baseHAM = 10100,
	baseHAMmax = 10100,
	armor = 0,
	resists = {0,60,0,-1,0,0,-1,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 41,
	boneType = "bone_avian",
	boneAmount = 46,
	milk = 0,
	tamingChance = 0.000000,
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

CreatureTemplates:addCreatureTemplate(radiant_lantern_bird, "radiant_lantern_bird")