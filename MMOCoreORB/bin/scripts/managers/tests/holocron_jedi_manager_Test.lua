package.path = package.path .. ";scripts/managers/?.lua"
require("holocron_jedi_manager")

EXPECTEDNUMBEROFPROFESSIONSTOGRIND = 6

describe("Holocron Jedi Manager", function()
	it("Defines the number of professions to master to 6", function()
		assert.same(EXPECTEDNUMBEROFPROFESSIONSTOGRIND, NUMBEROFPROFESSIONSTOMASTER)
	end)

	it("Get grindable profession list returns a list of at least the number of professions that has to be mastered", function()
		assert.is_true(EXPECTEDNUMBEROFPROFESSIONSTOGRIND <= table.getn(HolocronJediManager.getGrindableProfessionList()))
	end)

	it("The size of the grindable profession list is not affected when items are removed from it locally", function()
		local theList = HolocronJediManager.getGrindableProfessionList()
		local firstSize = table.getn(theList)
		table.remove(theList, 1)
		assert.are.equal(firstSize, table.getn(HolocronJediManager.getGrindableProfessionList()))
	end)

	it("Shall on call to onPlayerCreation call the add hologrind profession method of the lua player object the defined number of times", function()
		local creaturePointer = {}
		local playerPointer = {}
		addHologrindProfessionSpy = spy.new(function() end)
		local getPlayerObjectSpy = spy.new(function() return playerPointer end)
		local oldWithCreaturePlayerObject = HolocronJediManager.withCreaturePlayerObject
		HolocronJediManager.withCreaturePlayerObject = spy.new(function(pCreatureObject, performThisFunction)
			return performThisFunction({ addHologrindProfession = addHologrindProfessionSpy }) 
		end)

		HolocronJediManager.onPlayerCreated(creaturePointer)

		assert.spy(HolocronJediManager.withCreaturePlayerObject).was.called(1)
		assert.spy(addHologrindProfessionSpy).was.called(EXPECTEDNUMBEROFPROFESSIONSTOGRIND)

		HolocronJediManager.withCreaturePlayerObject = oldWithCreaturePlayerObject
	end)
end)
