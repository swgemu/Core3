lorne_prestar = Creature:new {
	objectName = "@mob/creature_names:mos_taike_guard_old",
	customName = "Lorne Prestar",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 20,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 5000,
	baseHAMmax = 6100,
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
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/mos_taike_guard_old.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "lorne_prestar_mission_giver_convotemplate",
	outfit = "mos_taike_guard_old_outfit",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(lorne_prestar, "lorne_prestar")