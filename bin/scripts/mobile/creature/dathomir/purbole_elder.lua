purbole_elder = Creature:new {
	objectName = "@mob/creature_names:purbole_elder",
	socialGroup = "Purbole",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.350000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2443,
	baseHAM = 8550,
	baseHAMmax = 8550,
	armor = 0,
	resists = {20,25,0,-1,-1,70,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 15,
	hideType = "hide_bristley",
	hideAmount = 11,
	boneType = "bone_mammal",
	boneAmount = 11,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/purbole_elder.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(purbole_elder, "purbole_elder")