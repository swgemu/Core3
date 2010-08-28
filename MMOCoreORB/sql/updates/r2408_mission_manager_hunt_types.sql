-- phpMyAdmin SQL Dump
-- version 3.3.5
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Aug 26, 2010 at 09:22 PM
-- Server version: 5.1.47
-- PHP Version: 5.3.3

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
-- Table structure for table `mission_manager_hunt_types`
--

USE swgemu;

DROP TABLE IF EXISTS `mission_manager_hunt_types`;
CREATE TABLE IF NOT EXISTS `mission_manager_hunt_types` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `zoneid` int(11) NOT NULL,
  `file1` varchar(100) NOT NULL,
  `file2` varchar(100) DEFAULT NULL,
  `level` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `mission_manager_hunt_types`
--

INSERT INTO `mission_manager_hunt_types` (`id`, `zoneid`, `file1`, `file2`, `level`) VALUES
(1, 5, 'object/mobile/capper_spineflap.iff', 'object/mobile/capper_spineflap_hue.iff', 1);
