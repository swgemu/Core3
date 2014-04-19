require("utils.helpers")

describe("Helpers", function()
	local item1 = { "item1" }
	local item2 = { "item2" }
	local item3 = { "item3" }
	local itemA = { "itemA" }
	local itemB = { "itemB" }
	local itemC = { "itemC" }
	local testTableNumbers = { item1, item2, item3 }
	local testTableLetters = { itemA, itemB, itemC }
	local mappingTable = {}

	setup(function()
	end)

	teardown(function()
	end)

	before_each(function()
		mappingTable[item1] = itemA
		mappingTable[item2] = itemB
		mappingTable[item3] = itemC
	end)

	describe("foreach", function()
		describe("When called with a list and a function", function()
			it("should call the function one time per item with the item as argument.", function()
				local calledWith = {}
				foreach(testTableNumbers, function(item)
					table.insert(calledWith, item)
				end)

				assert.same(testTableNumbers, calledWith)
			end)
		end)
	end)

	describe("map", function()
		describe("When called with a list and a function", function()
			it("Should call the function one time per item with the item as argument.", function()
				local calledWith = {}
				map(testTableNumbers, function(item)
					table.insert(calledWith, item)
					return nil
				end)

				assert.same(testTableNumbers, calledWith)
			end)

			it("Should return a value for each item.", function()
				assert.same(testTableLetters, map(testTableNumbers, function(item)
						return mappingTable[item]
					end))
			end)
		end)
	end)

	describe("filter", function()
		describe("When called with a list and a function", function()
			it("Should call the function one time per item with the item as argument.", function()
				local calledWith = {}
				filter(testTableNumbers, function(item)
					table.insert(calledWith, item)
					return nil
				end)

				assert.same(testTableNumbers, calledWith)
			end)

			it("Should return a table with only the items where the supplied function returns true.", function()
				local filteredTable = { item2 }
				assert.same(filteredTable, filter(testTableNumbers, function(item)
						return item == item2
					end))
			end)

			it("Should return an empty table if the supplied function returned false for all items.", function()
				local filteredTable = {}
				assert.same(filteredTable, filter(testTableNumbers, function(item)
						return false
					end))
			end)
		end)
	end)

	describe("first", function()
		describe("When called with a list and a function", function()
			it("Should call the function one time per item with the item as argument.", function()
				local calledWith = {}
				first(testTableNumbers, function(item)
					table.insert(calledWith, item)
					return nil
				end)

				assert.same(testTableNumbers, calledWith)
			end)

			it("Should return the first value that the supplied function returns true for.", function()
				assert.same(item2, first(testTableNumbers, function(item)
						return item == item2 or item == item3
					end))
			end)

			it("Should return nil if no item matched the requirement.", function()
				local filteredTable = { item2 }
				assert.same(nil, first(testTableNumbers, function(item)
						return false
					end))
			end)
		end)
	end)
end)
