local Logger = require("utils.logger")
require("utils.helpers")

spacestation_yavin4_conv_handler = Object:new {
}
function spacestation_yavin4_conv_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
    local creature = LuaCreatureObject(conversingPlayer)
    local convosession = creature:getConversationSession()
    lastConversation = nil
    local conversation = LuaConversationTemplate(conversationTemplate)
    local nextConversationScreen

    if (conversation ~= nil) then
        if (convosession ~= nil) then
            local session = LuaConversationSession(convosession)
            if (session ~= nil) then
                lastConversationScreen = session:getLastConversationScreen()
            end
        end
    end

    if (lastConversationScreen == nil) then
        nextConversationScreen = conversation:getScreen("spacestation_yavin4_greeting")
    else
        local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
        local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
        nextConversationScreen = conversation:getScreen(optionLink)

    end

    return nextConversationScreen

end

function spacestation_yavin4_conv_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)

    local player = LuaSceneObject(conversingPlayer)
    local screen = LuaConversationScreen(conversationScreen)
    local screenID = screen:getScreenID()
    local pConvScreen = screen:cloneScreen()
    local clonedConversation = LuaConversationScreen(pConvScreen)
    local pShip = SceneObject(conversingPlayer):getParent()

    if (screenID == "spacestation_yavin4_land_mining_land") then
        player:switchZone("yavin4", -267, 35, 4896, 0)
        LuaShipObject(pShip):storeShip(conversingPlayer)

    elseif (screenID == "spacestation_yavin4_land_labor_land") then
        player:switchZone("yavin4", -6921, 73, -5726, 0)
        LuaShipObject(pShip):storeShip(conversingPlayer)

    elseif (screenID == "spacestation_yavin4_land_imperial_land") then
        player:switchZone("yavin4", 4054, 37, -6216, 0)
        LuaShipObject(pShip):storeShip(conversingPlayer)
    end

    return pConvScreen
end
