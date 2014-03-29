apron_chef_s01 = {
 -- Chef's Apron
    minimumLevel = 0,
    maximumLevel = -1,
    customObjectName = "",
    directObjectTemplate = "object/tangible/wearables/apron/apron_chef_s01.iff",
    craftingValues = {},
    skillMods = {},
    customizationStringNames = {"/private/index_color_1","/private/index_color_2","/private/index_color_3"},
    customizationValues = {
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31},
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},
        {0,1,2}
    },
    junkDealerTypeNeeded = JUNKCLOTHESANDJEWELLERY,
    junkMinValue = 50,
    junkMaxValue = 100
}

addLootItemTemplate("apron_chef_s01", apron_chef_s01)