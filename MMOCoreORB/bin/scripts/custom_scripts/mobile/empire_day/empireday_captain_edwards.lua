empireday_captain_edwards = Creature:new {
	customName = "Captain Cheri Edwards (a SpecForce Guerrilla)",
	socialGroup = "rebel",
	faction = "rebel",
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

	templates = {"object/mobile/dressed_rebel_specforce_guerrilla_rodian_female_01.iff"},
	lootGroups = {},

	weapons = {"melee_weapons"},
	conversationTemplate = "EmpireDayCaptainEdwardsConvoTemplate",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(empireday_captain_edwards, "empireday_captain_edwards")