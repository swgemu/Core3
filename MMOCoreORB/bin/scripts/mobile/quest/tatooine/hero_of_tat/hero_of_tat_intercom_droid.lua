hero_of_tat_intercom_droid = Creature:new {
	objectName = "",
	customName = "Intercom Droid",
	socialGroup = "",
	faction = "",
	level = 4,
	chanceHit = 0.24,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 138,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 264,
	diet = HERBIVORE,

	templates = {"object/mobile/3po_protocol_droid.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "heroOfTatIntercomConvoTemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(hero_of_tat_intercom_droid, "hero_of_tat_intercom_droid")