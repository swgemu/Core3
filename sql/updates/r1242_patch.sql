ALTER TABLE `swgemu`.`characters` ADD COLUMN `home_location` TINYINT UNSIGNED AFTER `cloningFacility`,
 ADD COLUMN `bank_location` TINYINT UNSIGNED AFTER `home_location`;

ALTER TABLE `swgemu`.`character_items` ADD COLUMN `in_bank` TINYINT UNSIGNED;

ALTER TABLE `swgemu`.`character_items` ADD INDEX `container_ix`(`container`),
 ADD INDEX `deleted_ix`(`deleted`),
 ADD INDEX `char_ix`(`character_id`);

delete from terminals where type=2;
INSERT INTO `terminals` VALUES ('', '0', '2', '0', '0', '-0.412134', '0.911123', '-5134.47', '6.4', '4162.61', '5', '');
INSERT INTO `terminals` VALUES ('', '0', '2', '0', '0', '0.935007', '-0.354628', '-5133.65', '6.4', '4156.29', '5', '');
INSERT INTO `terminals` VALUES ('', '0', '2', '0', '0', '0.340543', '0.940229', '-5129.6', '6.4', '4164.21', '5', '');
