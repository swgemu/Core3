lethargic_behemoth = Creature:new {
	objectName = "@mob/creature_names:flit_lethargic_behemoth",
	socialGroup = "Flit",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.35,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2219,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {10,10,-1,-1,0,-1,0,0,-1},
	meatType = "meat_avian",
	meatAmount = 11,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 13,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_flit.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(lethargic_behemoth, "lethargic_behemoth")