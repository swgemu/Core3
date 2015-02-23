giant_gackle_bat = Creature:new {
	objectName = "@mob/creature_names:giant_gackle_bat",
	socialGroup = "gacklebat",
	faction = "",
	level = 24,
	chanceHit = 0.350000,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2443,
	baseHAM = 7550,
	baseHAMmax = 7550,
	armor = 0,
	resists = {115,120,-1,125,-1,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 7,
	hideType = "hide_bristley",
	hideAmount = 5,
	boneType = "bone_mammal",
	boneAmount = 6,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_gackle_bat.iff"},
	controlDeviceTemplate = "object/intangible/pet/gackle_bat_hue.iff",
	scale = 1.5,
	lootGroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_gackle_bat, "giant_gackle_bat")
