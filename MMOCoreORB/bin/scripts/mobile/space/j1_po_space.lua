j1_po_space = Creature:new {
	objectName = "@npc_spawner_n:j1_po",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 19,
	chanceHit = 0.33,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1257,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/space_rebel_tier1_naboo_v3fx.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(j1_po_space, "j1_po_space")
