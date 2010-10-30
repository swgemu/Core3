arachne_queen = Creature:new {
	objectName = "@mob/creature_names:queen_arachne",
	socialGroup = "Arachne",
	pvpFaction = "",
	faction = "",
	level = 63,
	chanceHit = 0.600000,
	damageMin = 445,
	damageMax = 600,
	baseXp = 6105,
	baseHAM = 12500,
	baseHAMmax = 12500,
	armor = 0,
	resists = {50,35,0,80,80,0,80,-1,-1},
	meatType = "meat_insect",
	meatAmount = 60,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/queen_arachne.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareapoison",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(arachne_queen, "arachne_queen")