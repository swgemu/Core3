hostile_huurton = Creature:new {
	objectName = "@mob/creature_names:warren_huurton_hostile",
	socialGroup = "Warren Huurton",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1257,
	baseHAM = 4550,
	baseHAMmax = 4550,
	armor = 0,
	resists = {0,0,0,0,-1,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 15,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/huurton.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(hostile_huurton, "hostile_huurton")