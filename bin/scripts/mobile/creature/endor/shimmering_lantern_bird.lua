shimmering_lantern_bird = Creature:new {
	objectName = "@mob/creature_names:shimmering_lantern_bird",
	socialGroup = "Lantern",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.370000,
	damageMin = 270,
	damageMax = 280,
	baseXp = 3005,
	baseHAM = 9100,
	baseHAMmax = 9100,
	armor = 0,
	resists = {30,45,0,-1,0,-1,-1,0,-1},
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
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(shimmering_lantern_bird, "shimmering_lantern_bird")