-- phpMyAdmin SQL Dump
-- version 3.3.7deb3build0.10.10.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Mar 03, 2011 at 01:43 PM
-- Server version: 5.1.49
-- PHP Version: 5.3.3-1ubuntu9.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `swgemu`
--

-- --------------------------------------------------------

--
-- Table structure for table `loottable`
--

CREATE TABLE IF NOT EXISTS `loottable` (
  `lootgroup` tinyint(4) DEFAULT NULL,
  `name` text NOT NULL,
  `template_crc` bigint(20) unsigned NOT NULL,
  `template_type` int(10) unsigned NOT NULL,
  `template_name` varchar(50) DEFAULT '',
  `container` bigint(20) unsigned NOT NULL DEFAULT '0',
  `attributes` text NOT NULL,
  `appearance` mediumtext NOT NULL,
  `chance` int(10) unsigned NOT NULL DEFAULT '100',
  `level` int(10) unsigned NOT NULL DEFAULT '0',
  `lastdropstamp` varchar(20) NOT NULL DEFAULT '0',
  `dontdropbefore` varchar(20) NOT NULL DEFAULT '0',
  `unique` int(10) unsigned NOT NULL DEFAULT '0',
  `notrade` int(10) unsigned NOT NULL DEFAULT '0',
  `race` varchar(150) NOT NULL DEFAULT 'all',
  `pix` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `itemMask` smallint(5) unsigned NOT NULL DEFAULT '65535',
  PRIMARY KEY (`pix`),
  KEY `lootgroup_ix` (`lootgroup`),
  KEY `chance_ix` (`chance`),
  KEY `lootlevel_ix` (`level`),
  FULLTEXT KEY `race_ix` (`race`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=454 ;

--
-- Dumping data for table `loottable`
--

INSERT INTO `loottable` (`lootgroup`, `name`, `template_crc`, `template_type`, `template_name`, `container`, `attributes`, `appearance`, `chance`, `level`, `lastdropstamp`, `dontdropbefore`, `unique`, `notrade`, `race`, `pix`, `itemMask`) VALUES
(4, 'Maroj Melon', 2356682898, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 427, 65535),
(4, 'Schule Nef', 3705347471, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 428, 65535),
(4, 'Alever Tweth''pek', 509800328, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 429, 65535),
(4, 'Etost''Ew Zann', 1848987926, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 430, 65535),
(4, 'Sijjo Sewi', 2894897937, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 431, 65535),
(4, 'Flurr-Cle Onion', 2513861122, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 432, 65535),
(4, 'Sosi Hodor', 657995419, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 433, 65535),
(4, 'Wild Snaff', 1466927109, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 434, 65535),
(4, 'Ko-Do Fruit', 3850486940, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 435, 65535),
(4, 'Jar of Foraged Fungus', 471067493, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 436, 65535),
(4, 'Jar of Foraged Grubs', 2811413371, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 437, 65535),
(4, 'Jar of Foraged Livers', 4212579566, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 438, 65535),
(4, 'Jar of Foraged Bugs', 3448226390, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 439, 65535),
(4, 'Jar of Foraged Berries', 1301924307, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 440, 65535),
(8, 'Worm Bait', 3486052108, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 441, 65535),
(8, 'Insect Bait', 1025045319, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 442, 65535),
(8, 'Grub Bait', 2051153781, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 443, 65535),
(5, 'Biological Effect Controller', 2874741112, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 445, 65535),
(5, 'Liquid Delivery Suspension', 3216390038, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 446, 65535),
(5, 'Chemical Release Duration Mechanism', 418150404, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 447, 65535),
(5, 'Solid Delivery Shell', 3737748835, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 448, 65535),
(6, 'Advanced Biological Effect Controller', 1952373811, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 449, 65535),
(6, 'Advanced Solid Delivery Shell', 1851480794, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 450, 65535),
(6, 'Advanced Chemical Release Duration Mechanism', 3985820000, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 451, 65535),
(6, 'Advanced Liquid Delivery Suspension', 2454210198, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 452, 65535),
(9, 'Treasure Map', 3932574781, 0, '', 0, '', '', 1, 1, '0', '0', 0, 0, 'all', 453, 65535);
