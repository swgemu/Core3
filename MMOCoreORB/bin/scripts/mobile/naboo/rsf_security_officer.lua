rsf_security_officer = Creature:new {
	objectName = "@mob/creature_names:rsf_security_officer",
	socialGroup = "naboo_security_force",
	pvpFaction = "naboo_security_force",
	faction = "naboo_security_force",
	level = 16,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 2900,
	baseHAMmax = 3500,
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_rsf_security_officer.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 4000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kits", chance = 4000000}
			},
			lootChance = 4800000
		}				
	},
	weapons = {"imperial_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(rsf_security_officer, "rsf_security_officer")