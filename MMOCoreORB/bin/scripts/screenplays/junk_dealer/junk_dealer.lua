JunkDealer = {
	junkTypes = {
		{"generic", 1},
		{"finery", 2},
		{"arms", 4},
		{"geo", 8},
		{"tusken", 16},
		{"jedi", 32},
		{"jawa", 64},
		{"gungan", 128},
		{"corsec", 256}
	}
}

function JunkDealer:sendSellJunkSelection(pPlayer, pNpc, dealerType, skipItem)
	if pPlayer == nil or pNpc == nil then
		return
	end

	local junkList = self:getEligibleJunk(pPlayer, dealerType, skipItem)

	if #junkList == 0 then
		CreatureObject(pPlayer):sendSystemMessage("@loot_dealer:no_items") -- You have no items that the junk dealer wishes to buy.
		deleteStringData(SceneObject(pPlayer):getObjectID() .. ":junkDealerType")
		return
	end

	local suiManager = LuaSuiManager()
	suiManager:sendListBox(pNpc, pPlayer, "@loot_dealer:sell_title", "@loot_dealer:sell_prompt", 3, "@cancel", "@loot_dealer:btn_sell_all", "@loot_dealer:btn_sell", "JunkDealer", "sellListSuiCallback", 10, junkList)
end

function JunkDealer:getDealerNum(dealerType)
	local dealerNum = 0

	for i = 1, #self.junkTypes, 1 do
		if string.find(dealerType, self.junkTypes[i][1]) ~= nil then
			dealerNum = self.junkTypes[i][2]
		end
	end

	return dealerNum
end

function JunkDealer:getEligibleJunk(pPlayer, dealerType, skipItem)
	local junkList = {}

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return junkList
	end

	local dealerNum = self:getDealerNum(dealerType)

	if dealerNum == 0 then
		return junkList
	end

	for i = 0, SceneObject(pInventory):getContainerObjectsSize() - 1, 1 do
		local pItem = SceneObject(pInventory):getContainerObject(i)

		if pItem ~= nil then
			local tano = TangibleObject(pItem)
			local sceno = SceneObject(pItem)

			if sceno:getObjectID() ~= skipItem then
				if tano:getJunkDealerNeeded() & dealerNum > 0 and tano:getCraftersName() == "" and not tano:isBroken() and not tano:isSliced() and not tano:isNoTrade() and sceno:getContainerObjectsSize() == 0 then
					local name = sceno:getDisplayedName()
					local value = tano:getJunkValue()
					local textTable = {"[" .. value .. "] " .. name, sceno:getObjectID()}
					table.insert(junkList, textTable)
				end
			end
		end
	end

	return junkList
end

function JunkDealer:sellListSuiCallback(pPlayer, pSui, eventIndex, otherPressed, rowIndex)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil or eventIndex == 1 then
		deleteStringData(SceneObject(pPlayer):getObjectID() .. ":junkDealerType")
		return
	end

	if (otherPressed == "true") then
		self:sellAllItems(pPlayer, pSui, pInventory)
	else
		rowIndex = tonumber(rowIndex)

		if (rowIndex == -1) then
			deleteStringData(SceneObject(pPlayer):getObjectID() .. ":junkDealerType")
			return
		end

		self:sellItem(pPlayer, pSui, rowIndex, pInventory)
	end
end

function JunkDealer:sellAllItems(pPlayer, pSui, pInventory)
	deleteStringData(SceneObject(pPlayer):getObjectID() .. ":junkDealerType")
	local listBox = LuaSuiListBox(pSui)
	local pNpc = listBox:getUsingObject()

	if pNpc == nil then
		return
	end

	local name = SceneObject(pNpc):getDisplayedName()
	local amount = 0

	for i = 0, listBox:getMenuSize() - 1, 1 do
		local oid = listBox:getMenuObjectID(i)
		local pItem = SceneObject(pInventory):getContainerObjectById(oid)

		if pItem ~= nil then
			local value = TangibleObject(pItem):getJunkValue()
			createEvent(10, "JunkDealer", "destroyItem", pItem, "")

			amount = amount + value
		end
	end

	CreatureObject(pPlayer):addCashCredits(amount, true)

	local messageString = LuaStringIdChatParameter("@loot_dealer:prose_sold_all_junk") -- You sell all of your loot to %TT for %DI credits
	messageString:setTT(name)
	messageString:setDI(amount)
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
end

function JunkDealer:destroyItem(pItem)
	if (pItem == nil) then
		return
	end

	SceneObject(pItem):destroyObjectFromWorld()
	SceneObject(pItem):destroyObjectFromDatabase()
end

function JunkDealer:sellItem(pPlayer, pSui, rowIndex, pInventory)
	local listBox = LuaSuiListBox(pSui)
	local pNpc = listBox:getUsingObject()
	local oid = listBox:getMenuObjectID(rowIndex)
	local pItem = SceneObject(pInventory):getContainerObjectById(oid)

	if pItem == nil or pNpc == nil then
		deleteStringData(SceneObject(pPlayer):getObjectID() .. ":junkDealerType")
		return
	end

	local item = SceneObject(pItem)
	local skipItem = item:getObjectID()
	local name = item:getDisplayedName()
	local value = TangibleObject(pItem):getJunkValue()

	createEvent(10, "JunkDealer", "destroyItem", pItem, "")

	CreatureObject(pPlayer):addCashCredits(value, true)

	local messageString = LuaStringIdChatParameter("@loot_dealer:prose_sold_junk") -- You sell %TT for %DI credits.
	messageString:setTT(name)
	messageString:setDI(value)
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())

	local dealerType = readStringData(SceneObject(pPlayer):getObjectID() .. ":junkDealerType")
	self:sendSellJunkSelection(pPlayer, pNpc, dealerType, skipItem)
end

return JunkDealer
