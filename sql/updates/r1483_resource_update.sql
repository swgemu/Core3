/*alter table resource_data change INDEX objectID;*/

ALTER TABLE `swgemu`.`resource_data` CHANGE COLUMN `INDEX` `objectID` INTEGER  NOT NULL DEFAULT NULL AUTO_INCREMENT,
 DROP PRIMARY KEY,
 ADD PRIMARY KEY  USING BTREE(`objectID`);

