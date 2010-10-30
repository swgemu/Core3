captain_hassk = Creature:new {
	objectName = "@mob/creature_names:captain_hassk",
	socialGroup = "Rorgungan",
	pvpFaction = "Rorgungan",
	faction = "",
	level = 73,
	chanceHit = 0.700000,
	damageMin = 495,
	damageMax = 700,
	baseXp = 7023,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 0,
	resists = {80,0,0,0,20,0,35,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER + HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"captain_hassk's_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(captain_hassk, "captain_hassk")