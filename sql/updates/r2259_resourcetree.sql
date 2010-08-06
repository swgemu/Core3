USE swgemu;

UPDATE resource_tree SET resourcecontainer = 'object/resource_container/resource_container_organic_bottle_milk.iff' WHERE resourcecontainer = 'object/resource_container/resource_container_bottle_milk.iff';
UPDATE resource_tree SET resourcecontainer = 'object/resource_container/resource_container_organic_bean.iff' WHERE resourcecontainer = 'object/resource_container/resource_container_organic_beans.iff';
UPDATE resource_tree SET resourcecontainer = 'object/resource_container/resource_container_organic_tuber.iff' WHERE resourcecontainer = 'object/resource_container/resource_container_organic_tubers.iff';