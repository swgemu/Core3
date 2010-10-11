mutant_bark_mite_soldier = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:mutant_bark_mite_soldier",
	socialGroup = "Mut. Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.330000,
	damageMin = 230,
	damageMax = 240,
	range = 25,
	baseXp = 2543,
	baseHAM = 6550,
	armor = 0,
	resists = {30,30,-1,20,20,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 25,
	hideType = "hide_bristley",
	hideAmount = 20,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(mutant_bark_mite_soldier, "mutant_bark_mite_soldier")
