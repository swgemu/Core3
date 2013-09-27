package.path = package.path .. ";scripts/managers/?.lua"
require("holocron_jedi_manager")

EXPECTEDNUMBEROFPROFESSIONSTOGRIND = 6

describe("Holocron Jedi Manager", function()
	it("Defines the number of professions to master to 6", function()
		assert.same(EXPECTEDNUMBEROFPROFESSIONSTOGRIND, NUMBEROFPROFESSIONSTOMASTER)
	end)

	it("Get grindable profession list returns a list of at least the number of professions that has to be mastered", function()
		assert.is_true(EXPECTEDNUMBEROFPROFESSIONSTOGRIND <= table.getn(HolocronJediManager:getGrindableProfessionList()))
	end)

	it("The size of the grindable profession list is not affected when items are removed from it locally", function()
		local theList = HolocronJediManager:getGrindableProfessionList()
		local firstSize = table.getn(theList)
		table.remove(theList, 1)
		assert.are.equal(firstSize, table.getn(HolocronJediManager:getGrindableProfessionList()))
	end)

	it("Shall on call to onPlayerCreation call the add hologrind profession method of the lua player object the defined number of times", function()
		local creaturePointer = {}
		local playerPointer = {}
		local addHologrindProfessionSpy = spy.new(function() end)
		local getPlayerObjectSpy = spy.new(function() return playerPointer end)
		LuaPlayerObject =  spy.new(function() return { addHologrindProfession = addHologrindProfessionSpy } end)
		LuaCreatureObject = spy.new(function() return { getPlayerObject = getPlayerObjectSpy } end)
		HolocronJediManager:onPlayerCreation(creaturePointer)

		assert.spy(LuaCreatureObject).was.called_with(creaturePointer)
		assert.spy(getPlayerObjectSpy).was.called(1)
		assert.spy(LuaPlayerObject).was.called_with(playerPointer)
		assert.spy(addHologrindProfessionSpy).was.called(EXPECTEDNUMBEROFPROFESSIONSTOGRIND)		
	end)

	it("Shall on call to onPlayerCreation if the creature pointer is equal to nil return without adding any hologrind professions", function()
		local creaturePointer = nil
		local playerPointer = {}
		local addHologrindProfessionSpy = spy.new(function() end)
		local getPlayerObjectSpy = spy.new(function() return playerPointer end)
		LuaPlayerObject =  spy.new(function() return { addHologrindProfession = addHologrindProfessionSpy } end)
		LuaCreatureObject = spy.new(function() return { getPlayerObject = getPlayerObjectSpy } end)
		HolocronJediManager:onPlayerCreation(creaturePointer)

		assert.spy(LuaCreatureObject).was_not_called()
		assert.spy(getPlayerObjectSpy).was_not_called()
		assert.spy(LuaPlayerObject).was_not_called()
		assert.spy(addHologrindProfessionSpy).was_not_called()		
	end)

	it("Shall on call to onPlayerCreation if the player returned from getPlayerObject is equal to nil return without adding any hologrind professions", function()
		local creaturePointer = {}
		local playerPointer = nil
		local addHologrindProfessionSpy = spy.new(function() end)
		local getPlayerObjectSpy = spy.new(function() return playerPointer end)
		LuaPlayerObject =  spy.new(function() return { addHologrindProfession = addHologrindProfessionSpy } end)
		LuaCreatureObject = spy.new(function() return { getPlayerObject = getPlayerObjectSpy } end)
		HolocronJediManager:onPlayerCreation(creaturePointer)

		assert.spy(LuaCreatureObject).was.called_with(creaturePointer)
		assert.spy(getPlayerObjectSpy).was.called(1)
		assert.spy(LuaPlayerObject).was_not_called()
		assert.spy(addHologrindProfessionSpy).was_not_called()		
	end)
end)
