bedraggled_korga_laborer = Creature:new {
	objectName = "@mob/creature_names:bedraggled_korga_laborer",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "korga_tribe",
	faction = "korga_tribe",
	level = 27,
	chanceHit = 0.37,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2730,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {0,0,0,20,20,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dulok_male.iff",
		"object/mobile/dulok_female.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(bedraggled_korga_laborer, "bedraggled_korga_laborer")
