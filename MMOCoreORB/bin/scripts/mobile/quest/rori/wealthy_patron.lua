wealthy_patron = Creature:new {
	objectName = "",
	customName = "a wealthy patron",
	socialGroup = "",
	faction = "",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 700,
	baseHAMmax = 800,
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
	creatureBitmask = NONE,
	optionsBitmask = INVULNERABLE + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_noble_twilek_female_01.iff"},
	lootGroups = {				
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "hefsen_zindalai_mission_target_convotemplate",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(wealthy_patron, "wealthy_patron")
