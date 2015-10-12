includeAiFile("tasks/compositebase.lua")

Composite = createClass(CompositeBase, Interrupt)
CompositeDefault = createClass(CompositeBase, DefaultInterrupt)
CompositePack = createClass(CompositeBase, PackInterrupt)
CompositeCreaturePet = createClass(CompositeBase, CreaturePetInterrupt)
CompositeDroidPet = createClass(CompositeBase, DroidPetInterrupt)
CompositeFactionPet = createClass(CompositeBase, FactionPetInterrupt)
