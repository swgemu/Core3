huurton_howler = Creature:new {
	objectName = "@mob/creature_names:huurton_howler",
	socialGroup = "Huurton",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.350000,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2637,
	baseHAM = 6000,
	baseHAMmax = 6000,
	armor = 0,
	resists = {15,15,0,40,60,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 15,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 15,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/huurton.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(huurton_howler, "huurton_howler")