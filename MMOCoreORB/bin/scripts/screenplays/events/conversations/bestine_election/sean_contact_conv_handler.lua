local ObjectManager = require("managers.object.object_manager")

seanContactConvoHandler = Object:new {
    themePark = nil
}


function seanContactConvoHandler:setThemePark(themeParkNew)
  self.themePark = themeParkNew
end


function seanContactConvoHandler:hasHistoryDisk(pPlayer)
local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
if pInventory == nil then
  return false
 end

 local pHistoryDisk = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff", true)
 if (pHistoryDisk ~= nil) and (getQuestStatus("bestine_election:electionWinner") == "Sean") then
  return true
 end
 return false
end

function seanContactConvoHandler:destroyHDisk(pPlayer)
  if (pPlayer == nil) then
    return
  end

  local pObj = CreatureObject(pPlayer):getPlayerObject()
  local playerID = CreatureObject(pPlayer):getObjectID()
  local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
  local hDisk = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff" , true)
  if hDisk ~= nil then
      SceneObject(hDisk):destroyObjectFromWorld()
      SceneObject(hDisk):destroyObjectFromDatabase()
  end
  writeData(playerID..":bestine_election:disk_destroyed",1)
  deleteData(playerID..":bestine_election:seanContact")

  local wayID = readData(playerID .. ":bestine_election:contactWaypointID")
  PlayerObject(pObj):removeWaypoint(wayID, true)
  deleteData(playerID .. ":bestine_election:contactWaypointID")
  return
end


function seanContactConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
  local convoTemplate = LuaConversationTemplate(pConversationTemplate)


  if  self:hasHistoryDisk(pPlayer) then
    return convoTemplate:getScreen("sean_inOffice_hasItem")
  end
   if (getQuestStatus("bestine_election:electionWinner") == "Sean")  then
    return convoTemplate:getScreen("sean_inOffice_noItem")
  end
  return convoTemplate:getScreen("sean_notinOffice")
end

function seanContactConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
  local screen = LuaConversationScreen(conversationScreen)
  local screenID = screen:getScreenID()
  local conversationScreen = screen:cloneScreen()
  local clonedConversation = LuaConversationScreen(conversationScreen)

  if screenID == "seanContact_itemDestroyed" then
    self:destroyHDisk(conversingPlayer)
  end
  print(screenID)
  return conversationScreen
end

function seanContactConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
  local pConversationSession = CreatureObject(pPlayer):getConversationSession()

  local pLastConversationScreen = nil

  if (pConversationSession ~= nil) then
    local conversationSession = LuaConversationSession(pConversationSession)
    pLastConversationScreen = conversationSession:getLastConversationScreen()
  end

  local conversationTemplate = LuaConversationTemplate(pConversationTemplate)

  if (pLastConversationScreen ~= nil) then
    local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
    local optionLink = lastConversationScreen:getOptionLink(selectedOption)

    return conversationTemplate:getScreen(optionLink)
  end

  return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end

