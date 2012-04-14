corsec_security_specialist = Creature:new {
	objectName = "@mob/creature_names:corsec_detective_aggro",
	socialGroup = "Corsec [aggro]",
	pvpFaction = "Corsec [aggro]",
	faction = "",
	level = 120,
	chanceHit = 4,
	damageMin = 745,
	damageMax = 1200,
	baseXp = 11390,
	baseHAM = 44000,
	baseHAMmax = 54000,
	armor = 2,
	resists = {50,50,30,15,80,30,15,35,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/object/mobile/shared_dressed_corellia_local_corsec_chief.iff.iff"},
	lootGroups = {
	  {
			groups = {
				{group = "clothing_attachments", chance = 2500000},
				{group = "armor_attachments", chance = 2500000},
				{group = "corsec_weapons", chance = 2500000},
				{group = "crystals", chance = 2500000}
			},
			lootChance = 6500000
		}
	},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(corsec_security_specialist, "corsec_security_specialist")