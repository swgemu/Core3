langlatch_destroyer = Creature:new {
	objectName = "@mob/creature_names:langlatch_destroyer",
	socialGroup = "Langlatch",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.320000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1803,
	baseHAM = 2700,
	baseHAMmax = 2700,
	armor = 0,
	resists = {20,0,0,15,15,45,45,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 18,
	hideType = "hide_wooly",
	hideAmount = 10,
	boneType = "bone_mammal",
	boneAmount = 10,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/langlatch.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(langlatch_destroyer, "langlatch_destroyer")