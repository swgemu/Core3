ko_do_fruit = {
	minimumLevel = 0,
	maximumLevel = -1,
	chance = 1.0, -- min 0.00001
	customObjectName = "Ko-Do Fruit",
	directObjectTemplate = "object/tangible/food/foraged/foraged_fruit_s4.iff" -- if this value is set all the below values are ignored
}

addLootItemTemplate("ko_do_fruit", ko_do_fruit)
