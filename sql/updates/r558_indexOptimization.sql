ALTER TABLE `swgemu`.`performance` ADD COLUMN `ix` INTEGER UNSIGNED NOT NULL DEFAULT NULL AUTO_INCREMENT , ADD PRIMARY KEY (ix);
ALTER TABLE `swgemu`.`trainers` ADD COLUMN `pix` INTEGER UNSIGNED NOT NULL DEFAULT NULL AUTO_INCREMENT ,  ADD PRIMARY KEY (pix);
ALTER TABLE `swgemu`.`trainers` ADD INDEX `planetIX`(`Planet`);
ALTER TABLE `swgemu`.`shuttles` ADD INDEX `planetIX`(`planet_id`);

ALTER TABLE `swgemu`.`resource_data` 
 ADD INDEX `name_ix`(`resource_name`),
 ADD INDEX `class_ix_1`(`class_1`),
 ADD INDEX `class_ix_2`(`class_2`),
 ADD INDEX `class_ix_3`(`class_3`),
 ADD INDEX `class_ix_4`(`class_4`),
 ADD INDEX `class_ix_5`(`class_5`),
 ADD INDEX `class_ix_6`(`class_6`),
 ADD INDEX `class_ix_7`(`class_7`);
 
ALTER TABLE `swgemu`.`resource_spawns` ADD INDEX `despawn_ix`(`despawn`);
ALTER TABLE `swgemu`.`resource_spawns` ADD INDEX `name_ix`(`resource_name`), ADD INDEX `pool_ix`(`pool`);
ALTER TABLE `swgemu`.`performance` ADD INDEX `iAudio_ix`(`instrumentAudioId`), ADD INDEX `iDance_ix`(`danceVisualId`);
ALTER TABLE `swgemu`.`staticobjects` ADD FULLTEXT INDEX `file_ix`(`file`);
