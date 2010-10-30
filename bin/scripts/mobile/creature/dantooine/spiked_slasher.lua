spiked_slasher = Creature:new {
	objectName = "@mob/creature_names:voritor_spiked_slasher",
	socialGroup = "Voritor Lizard",
	pvpFaction = "",
	faction = "",
	level = 58,
	chanceHit = 0.530000,
	damageMin = 430,
	damageMax = 570,
	baseXp = 5647,
	baseHAM = 11500,
	baseHAMmax = 11500,
	armor = 0,
	resists = {65,40,0,0,50,-1,20,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_leathery",
	hideAmount = 40,
	boneType = "bone_avian",
	boneAmount = 50,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/voritor_lizard.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"strongpoison",""},
		{"creatureareapoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(spiked_slasher, "spiked_slasher")