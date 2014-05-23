oxil_sarban_missions =
  {
    {
      missionType = "retrieve",
      primarySpawns =
      {
        { npcTemplate = "oxil_artisan", planetName = "rori", npcName = "an Artisan" }
      },
      secondarySpawns = {},
      itemSpawns =
      {
        { itemTemplate = "object/tangible/mission/quest_item/oxil_sarban_q1_needed.iff", itemName = "Rising Artist Presentation" }
      },
      rewards =
      {
        { rewardType = "credits", amount = 25 },
      }
    },
    {
      missionType = "retrieve",
      primarySpawns =
      {
        { npcTemplate = "oxil_art_dealer", planetName = "rori", npcName = "an Art Dealer" }
      },
      secondarySpawns = {},
      itemSpawns =
      {
        { itemTemplate = "object/tangible/mission/quest_item/oxil_sarban_q2_needed.iff", itemName = "Alien Dust Artifacts" }
      },
      rewards =
      {
        { rewardType = "credits", amount = 50 },
      }
    }
  }

npcMapOxilSarban =
  {
    {
      spawnData = { planetName = "rori", npcTemplate = "oxil_sarban", x = 28.6, z = 2.1, y = 75.3, direction = -144, cellID = 4635403, position = STAND },
      worldPosition = { x = -5000, y = -2261 },
      npcNumber = 1,
      stfFile = "@static_npc/rori/rori_narmle_oxil_sarban",
      missions = oxil_sarban_missions
    },

  }

OxilSarban = ThemeParkLogic:new {
  numberOfActs = 1,
  npcMap = npcMapOxilSarban,
  className = "OxilSarban",
  screenPlayState = "oxil_sarban_quest",
  distance = 800
}

registerScreenPlay("OxilSarban", true)

oxil_sarban_mission_giver_conv_handler = mission_giver_conv_handler:new {
  themePark = OxilSarban
}
oxil_sarban_mission_target_conv_handler = mission_target_conv_handler:new {
  themePark = OxilSarban
}