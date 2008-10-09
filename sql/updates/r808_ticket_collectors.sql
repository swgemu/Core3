/*
MySQL Data Transfer
Source Host: localhost
Source Database: swgemu
Target Host: localhost
Target Database: swgemu
Date: 10/9/2008 3:05:54 PM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for ticket_collectors
-- ----------------------------
CREATE TABLE `ticket_collectors` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `transport_id` int(11) NOT NULL,
  `parent` bigint(20) unsigned NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `dir_y` float NOT NULL,
  `dir_w` float NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `SECONDARY` (`transport_id`)
) ENGINE=MyISAM AUTO_INCREMENT=58 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `ticket_collectors` VALUES ('1', '1', '0', '6938', '-5528', '330.6', '-0.64', '0.8');
INSERT INTO `ticket_collectors` VALUES ('2', '2', '0', '6637', '-5931', '330.6', '0.75', '0.8');
INSERT INTO `ticket_collectors` VALUES ('3', '3', '0', '-338', '-4634', '28.6', '1', '0');
INSERT INTO `ticket_collectors` VALUES ('4', '4', '0', '-34.2', '-4402', '28.6', '1', '0');
INSERT INTO `ticket_collectors` VALUES ('5', '5', '0', '3078.5', '4984.5', '280.6', '0.75', '0.8');
INSERT INTO `ticket_collectors` VALUES ('6', '6', '0', '-3783.5', '3240.5', '86.6', '1', '0');
INSERT INTO `ticket_collectors` VALUES ('7', '7', '0', '-4992', '-2354', '21.6', '0', '0.8');
INSERT INTO `ticket_collectors` VALUES ('8', '8', '0', '-5607', '-2799', '21.6', '0.75', '0.8');
INSERT INTO `ticket_collectors` VALUES ('9', '9', '0', '-5560', '-6053', '16.6', '1', '0');
INSERT INTO `ticket_collectors` VALUES ('10', '10', '0', '1589', '-6410.4', '4', '-0.56', '0.82');
INSERT INTO `ticket_collectors` VALUES ('11', '11', '0', '-4229', '-2355.5', '3', '0.83', '0.55');
INSERT INTO `ticket_collectors` VALUES ('12', '12', '0', '-644', '2488', '3', '0.83', '0.55');
INSERT INTO `ticket_collectors` VALUES ('13', '13', '0', '-68.9', '-1578', '18', '0.93', '0.34');
INSERT INTO `ticket_collectors` VALUES ('14', '14', '0', '598', '3095', '6', '0.91', '0.43');
INSERT INTO `ticket_collectors` VALUES ('15', '15', '0', '3222', '-3493', '24', '0.52', '-0.84');
INSERT INTO `ticket_collectors` VALUES ('16', '16', '0', '-970', '1563', '73', '-0.52', '0.84');
INSERT INTO `ticket_collectors` VALUES ('17', '17', '0', '459', '5503', '8.8', '0.78', '0.62');
INSERT INTO `ticket_collectors` VALUES ('18', '18', '0', '5339', '-1567', '327.7', '-0.71', '0.7');
INSERT INTO `ticket_collectors` VALUES ('19', '19', '0', '5134', '6616.4', '-191.4', '0.42', '-0.83');
INSERT INTO `ticket_collectors` VALUES ('20', '20', '0', '2028', '2534', '19.7', '-0.71', '0.7');
INSERT INTO `ticket_collectors` VALUES ('21', '21', '0', '1558', '2845', '25.7', '1', '0');
INSERT INTO `ticket_collectors` VALUES ('22', '22', '0', '-5487', '-13', '-149.4', '-0.71', '0.7');
INSERT INTO `ticket_collectors` VALUES ('23', '23', '0', '4968.6', '-4883.7', '4.4', '-0.71', '0.7');
INSERT INTO `ticket_collectors` VALUES ('24', '24', '0', '-5863', '4163', '6.8', '0.72', '0.69');
INSERT INTO `ticket_collectors` VALUES ('25', '25', '0', '-5402', '4315', '6.8', '0', '1');
INSERT INTO `ticket_collectors` VALUES ('26', '26', '0', '-5004.5', '4086', '6.6', '-0.94', '0.38');
INSERT INTO `ticket_collectors` VALUES ('27', '27', '0', '-5256.4', '-2150.4', '81.3', '0.92', '-0.38');
INSERT INTO `ticket_collectors` VALUES ('28', '28', '0', '3668', '-6409', '96', '1', '0');
INSERT INTO `ticket_collectors` VALUES ('29', '29', '0', '5205', '5797', '80.7', '1', '0');
INSERT INTO `ticket_collectors` VALUES ('30', '30', '0', '707', '-3047', '6.6', '0', '0.8');
INSERT INTO `ticket_collectors` VALUES ('31', '31', '0', '-2222', '2298', '20', '0.17', '1');
INSERT INTO `ticket_collectors` VALUES ('32', '32', '0', '4328', '5422', '10.6', '0.75', '0.8');
INSERT INTO `ticket_collectors` VALUES ('33', '33', '0', '38', '-5332', '52.6', '1', '0');
INSERT INTO `ticket_collectors` VALUES ('34', '34', '0', '-1090', '-3554.9', '12.6', '-0.64', '0.76');
INSERT INTO `ticket_collectors` VALUES ('35', '35', '0', '3427.5', '-4642', '5.6', '-0.51', '0.8');
INSERT INTO `ticket_collectors` VALUES ('36', '36', '0', '1720', '3191', '7.6', '1', '0');
INSERT INTO `ticket_collectors` VALUES ('37', '37', '0', '-2792', '2179', '5.6', '-0.15', '0.8');
INSERT INTO `ticket_collectors` VALUES ('38', '38', '0', '-3116', '2165', '5.6', '0.6', '0.8');
INSERT INTO `ticket_collectors` VALUES ('39', '39', '0', '4032', '-6222', '37', '0.81', '0.57');
INSERT INTO `ticket_collectors` VALUES ('40', '40', '0', '-6927', '-5704', '73', '1', '0.22');
INSERT INTO `ticket_collectors` VALUES ('41', '41', '0', '-288', '4890', '35', '0.85', '0.52');
INSERT INTO `ticket_collectors` VALUES ('42', '42', '1692104', '-3.20424', '2.9712', '7.9418', '0.933335', '0.35898');
INSERT INTO `ticket_collectors` VALUES ('43', '43', '0', '4715.31', '-4656.65', '4.17', '0.996648', '-0.0818144');
INSERT INTO `ticket_collectors` VALUES ('44', '44', '0', '1344.26', '2762.17', '13', '1', '0');
INSERT INTO `ticket_collectors` VALUES ('45', '45', '0', '5290', '6655', '-192', '0', '1');
INSERT INTO `ticket_collectors` VALUES ('46', '46', '0', '3367', '5612', '308', '0.64', '0.75');
INSERT INTO `ticket_collectors` VALUES ('47', '47', '0', '-3149', '2895', '31', '0.8', '0.61');
INSERT INTO `ticket_collectors` VALUES ('48', '48', '0', '-4986', '-2218', '21', '0.48', '0.87');
INSERT INTO `ticket_collectors` VALUES ('49', '49', '9', '-51', '-4722', '28', '0.62', '0.78');
INSERT INTO `ticket_collectors` VALUES ('52', '52', '0', '245', '-2940', '6', '1', '0');
INSERT INTO `ticket_collectors` VALUES ('53', '53', '0', '4469', '5373', '2', '0.83', '-0.55');
INSERT INTO `ticket_collectors` VALUES ('54', '54', '0', '1252', '3059', '7', '0.73', '0.67');
INSERT INTO `ticket_collectors` VALUES ('55', '55', '0', '-2820', '2091', '5', '0.39', '1');
INSERT INTO `ticket_collectors` VALUES ('56', '56', '0', '3621', '-4785', '5', '-0.15', '1');
INSERT INTO `ticket_collectors` VALUES ('57', '57', '0', '-1377', '-3587', '12', '1', '0');
