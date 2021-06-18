empireday_captain_alrezrin = Creature:new {
	customName = "Captain Alrez-rin (a Imperial Royal Guard)",
	socialGroup = "imperial",
	faction = "imperial",
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
	pvpBitmask = NONE,
	creatureBitmask = HERD,
	optionsBitmask = INVULNERABLE + CONVERSABLE + INTERESTING,
	diet = HERBIVORE,

	templates = {"object/mobile/royal_guard.iff"},
	lootGroups = {},

	weapons = {"melee_weapons"},
	conversationTemplate = "EmpireDayCaptainAlrezrinConvoTemplate",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(empireday_captain_alrezrin, "empireday_captain_alrezrin")