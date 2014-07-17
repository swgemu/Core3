jaleela_bindoo_missions =
  {
    {
      missionType = "retrieve",
      primarySpawns =
      {
        { npcTemplate = "odoof_grunda", planetName = "rori", npcName = "Odoof Grunda" }
      },
      secondarySpawns = {},
      itemSpawns =
      {
        { itemTemplate = "object/tangible/mission/quest_item/jaleela_bindoo_q1_needed.iff", itemName = "Grunda Painting" }
      },
      rewards =
      {
        { rewardType = "credits", amount = 25 },
      }
    },
    {
      missionType = "escort",
      primarySpawns =
      {
        { npcTemplate = "jonda_trask", planetName = "rori", npcName = "Jonda Trask" }
      },
      secondarySpawns = {},
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 50 },
      }
    },
    {
      missionType = "deliver",
      primarySpawns =
      {
        { npcTemplate = "jaleela_imperial_courier", planetName = "rori", npcName = "Imperial Courier" }
      },
      secondarySpawns = {},
      itemSpawns =
      {
        { itemTemplate = "object/tangible/mission/quest_item/jaleela_bindoo_q3_needed.iff", itemName = "" }
      },
      rewards =
      {
        { rewardType = "credits", amount = 100 }
      }
    },
    {
      missionType = "escort",
      primarySpawns =
      {
        { npcTemplate = "jaleela_zim_graedler", planetName = "rori", npcName = "Zim Graedler" }
      },
      secondarySpawns = {
        { npcTemplate = "jaleela_protestor_leader", planetName = "rori", npcName = "Protestor Leader" },
        { npcTemplate = "jaleela_protestor", planetName = "rori", npcName = "a Protestor" },
        { npcTemplate = "jaleela_protestor", planetName = "rori", npcName = "a Protestor" }
      },
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 200 },
      }
    },
  }

npcMapJaleelaBindoo =
  {
    {
      spawnData = { planetName = "rori", npcTemplate = "jaleela_bindoo", x = -11.0, z = 1.7, y = -21.1, direction = 34, cellID = 4635527, position = STAND },
      worldPosition = { x = -5212, y = -2470 },
      npcNumber = 1,
      stfFile = "@static_npc/rori/rori_narmle_jaleela_bindoo",
      missions = jaleela_bindoo_missions
    },

  }

JaleelaBindoo = ThemeParkLogic:new {
  numberOfActs = 1,
  npcMap = npcMapJaleelaBindoo,
  className = "JaleelaBindoo",
  screenPlayState = "jaleela_bindoo_quest",
  distance = 800
}

registerScreenPlay("JaleelaBindoo", true)

jaleela_bindoo_mission_giver_conv_handler = mission_giver_conv_handler:new {
  themePark = JaleelaBindoo
}
jaleela_bindoo_mission_target_conv_handler = mission_target_conv_handler:new {
  themePark = JaleelaBindoo
}