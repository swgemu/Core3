bone_angler = Creature:new {
	objectName = "@mob/creature_names:angler_bone",
	socialGroup = "Angler",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.370000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2730,
	baseHAM = 8550,
	baseHAMmax = 8550,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 4,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/angler.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"strongpoison",""},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bone_angler, "bone_angler")