
mabari_armor_helmet_quest = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/tangible/wearables/armor/zam/armor_zam_wesell_helmet_quest.iff",
	craftingValues = {
	         {"armor_rating",1,1,0},
	         {"armor_effectiveness",10,15,10},
             {"kineticeffectiveness",10,15,10},
	         {"energyeffectiveness",10,15,10},
	         {"heateffectiveness",10,15,10},
	         {"blasteffectiveness",5,5,10},
	         {"armor_integrity",17000,17000,0},
	         {"armor_health_encumbrance",25,15,0},
	         {"armor_action_encumbrance",22,13,0},
	         {"armor_mind_encumbrance",300,180,0},
	},
	customizationStringNames = {},
	customizationValues = {}
}

addLootItemTemplate("mabari_armor_helmet_quest", mabari_armor_helmet_quest)