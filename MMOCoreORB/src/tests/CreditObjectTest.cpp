/*
 * CreditObjectTest.cpp
 *
 *  Created on: Sat Mar 21 15:58:31 UTC 2020
 *      Author: lordkator
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "server/zone/objects/creature/credits/CreditObject.h"
#include "server/zone/managers/credit/CreditManager.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::TypedEq;
using ::testing::An;

class CreditObjectTest : public ::testing::Test {
protected:
	bool isVerbose = false;
	int startCash = 987654321;
	int startBank = 123456789;
	bool origEnableAddr2Line;
	StringBuffer stackTraceOutput;
	StringBuffer creditManagerLogOutput;
	Locker* locker = nullptr;
	Reference<CreditManager*> creditManager = nullptr;
	Reference<CreditObject*> creditObject = nullptr;
public:
	CreditObjectTest() {
		creditManager = CreditManager::instance();
		creditObject = new CreditObject();
		locker = new Locker(creditObject);
		creditObject->setCashCredits(startCash, false);
		creditObject->setBankCredits(startBank, false);
		show("BEGIN");
	}

	~CreditObjectTest() {
		show("END");

		if (locker != nullptr) {
			locker->release();
			delete locker;
			locker = nullptr;
		}
	}

	void setVerbose(bool verbose) {
		isVerbose = verbose;
	}

	void SetUp() {
		// Configure StackTrace so we can capture its output
		origEnableAddr2Line = Core::getIntProperty("StackTrace.enableAddr2Line", 1);
		Core::setIntProperty("StackTrace.enableAddr2Line", 0);
		auto logger = StackTrace::getLogger();

		logger->setLogToConsole(false);

		logger->setLoggerCallback([=] (Logger::LogLevel level, const char* msg) -> int {
				stackTraceOutput << msg;
				return Logger::SUCCESS;
		});

		// Capture log output from CreditManager
		creditManager->setLoggerCallback([=] (Logger::LogLevel level, const char* msg) -> int {
				creditManagerLogOutput << msg;

				if (isVerbose) {
					std::cerr << "[>>>>>>>>> ]    Log Message: " << msg << std::endl;
				}

				return Logger::SUCCESS;
		});
	}

	void TearDown() {
		// Restore StackTrace to its original state
		auto logger = StackTrace::getLogger();
		Core::setIntProperty("StackTrace.enableAddr2Line", origEnableAddr2Line);
		logger->clearLoggerCallback();
		creditManager->setLogToConsole(false);
		creditManager->clearLoggerCallback();
	}

	void show(const char* state = ">>>>>>>>>") {
		std::cerr << "[" << std::setw(9) << state << " ] ";
		std::cerr << creditObject->toStringData().toCharArray() << std::endl;
	}
};

TEST_F(CreditObjectTest, CheckStartBalances) {
	ASSERT_EQ(creditObject->getBankCredits(), startBank);
	ASSERT_EQ(creditObject->getCashCredits(), startCash);
}

TEST_F(CreditObjectTest, AddCash) {
	int randomAmt = System::random(50000);
	auto current = creditObject->getCashCredits();
	creditObject->addCashCredits(randomAmt, false);
	ASSERT_EQ(creditObject->getCashCredits(), current + randomAmt);
}

TEST_F(CreditObjectTest, AddBank) {
	int randomAmt = System::random(50000);
	auto current = creditObject->getBankCredits();
	creditObject->addBankCredits(randomAmt, false);
	ASSERT_EQ(creditObject->getBankCredits(), current + randomAmt);
}

TEST_F(CreditObjectTest, SubtractCash) {
	auto current = creditObject->getCashCredits();
	int randomAmt = System::random(current);
	creditObject->subtractCashCredits(randomAmt, false);
	ASSERT_EQ(creditObject->getCashCredits(), current - randomAmt);
}

TEST_F(CreditObjectTest, SubtractBank) {
	auto current = creditObject->getBankCredits();
	int randomAmt = System::random(current);
	creditObject->subtractBankCredits(randomAmt, false);
	ASSERT_EQ(creditObject->getBankCredits(), current - randomAmt);
}

TEST_F(CreditObjectTest, OverdraftCash) {
	auto currentCash = creditObject->getCashCredits();
	auto currentBank = creditObject->getBankCredits();
	int randomAmt = System::random(currentBank / 2);

	creditObject->subtractCashCredits(currentCash + randomAmt, false);

	ASSERT_TRUE(creditManagerLogOutput.toString().contains("Overdraft"));
	ASSERT_TRUE(stackTraceOutput.length() > 0);
	ASSERT_EQ(creditObject->getCashCredits(), 0);
	ASSERT_EQ(creditObject->getBankCredits(), currentBank - randomAmt);
}

TEST_F(CreditObjectTest, OverdraftBank) {
	auto currentCash = creditObject->getCashCredits();
	auto currentBank = creditObject->getBankCredits();
	int randomAmt = System::random(currentCash / 2);

	creditObject->subtractBankCredits(currentBank + randomAmt, false);

	ASSERT_TRUE(creditManagerLogOutput.toString().contains("Overdraft"));
	ASSERT_TRUE(stackTraceOutput.length() > 0);
	ASSERT_EQ(creditObject->getCashCredits(), currentCash - randomAmt);
	ASSERT_EQ(creditObject->getBankCredits(), 0);
}

TEST_F(CreditObjectTest, Bankrupt) {
	auto currentCash = creditObject->getCashCredits();
	auto currentBank = creditObject->getBankCredits();
	int randomAmt = System::random(currentCash / 2);

	creditObject->subtractCashCredits(CreditObject::CREDITCAP);

	ASSERT_TRUE(creditManagerLogOutput.toString().contains("Overdraft"));
	ASSERT_TRUE(stackTraceOutput.length() > 0);
	ASSERT_EQ(creditObject->getCashCredits(), 0);
	ASSERT_EQ(creditObject->getBankCredits(), 0);
	creditManagerLogOutput.deleteAll();

	creditObject->subtractCashCredits(CreditObject::CREDITCAP);

	ASSERT_TRUE(creditManagerLogOutput.toString().contains("bankrupt"));
	ASSERT_TRUE(stackTraceOutput.length() > 0);
	ASSERT_EQ(creditObject->getCashCredits(), 0);
	ASSERT_EQ(creditObject->getBankCredits(), 0);
}

TEST_F(CreditObjectTest, OverflowCash) {
	auto currentCash = creditObject->getCashCredits();
	auto currentBank = creditObject->getBankCredits();
	int cap = CreditObject::CREDITCAP;
	int addAmt = cap;

	creditObject->addCashCredits(addAmt, false);

	ASSERT_TRUE(creditManagerLogOutput.toString().contains("Overflow"));
	ASSERT_TRUE(stackTraceOutput.length() > 0);
	ASSERT_EQ(creditObject->getCashCredits(), cap);
	ASSERT_EQ(creditObject->getBankCredits(), currentCash + currentBank);
}

TEST_F(CreditObjectTest, OverflowBank) {
	auto currentCash = creditObject->getCashCredits();
	auto currentBank = creditObject->getBankCredits();
	int cap = CreditObject::CREDITCAP;
	int addAmt = cap;

	creditObject->addBankCredits(addAmt, false);

	ASSERT_TRUE(creditManagerLogOutput.toString().contains("Overflow"));
	ASSERT_TRUE(stackTraceOutput.length() > 0);
	ASSERT_EQ(creditObject->getCashCredits(), currentCash + currentBank);
	ASSERT_EQ(creditObject->getBankCredits(), cap);
}

TEST_F(CreditObjectTest, OverflowCashToBank) {
	auto currentCash = creditObject->getCashCredits();
	auto currentBank = creditObject->getBankCredits();
	int cap = CreditObject::CREDITCAP;

	creditObject->addCashCredits(CreditObject::CREDITCAP, false);

	ASSERT_TRUE(creditManagerLogOutput.toString().contains("Overflow"));
	ASSERT_TRUE(stackTraceOutput.length() > 0);
	ASSERT_EQ(creditObject->getCashCredits(), cap);
	ASSERT_EQ(creditObject->getBankCredits(), currentCash + currentBank);
	creditManagerLogOutput.deleteAll();

	creditObject->addCashCredits(CreditObject::CREDITCAP, false);

	ASSERT_TRUE(creditManagerLogOutput.toString().contains("CREDITCAP"));
	ASSERT_TRUE(stackTraceOutput.length() > 0);
	ASSERT_EQ(creditObject->getCashCredits(), cap);
	ASSERT_EQ(creditObject->getBankCredits(), cap);
	creditManagerLogOutput.deleteAll();
}

TEST_F(CreditObjectTest, OverflowBankToCash) {
	auto currentCash = creditObject->getCashCredits();
	auto currentBank = creditObject->getBankCredits();
	int cap = CreditObject::CREDITCAP;

	creditObject->addBankCredits(CreditObject::CREDITCAP, false);

	ASSERT_TRUE(creditManagerLogOutput.toString().contains("Overflow"));
	ASSERT_TRUE(stackTraceOutput.length() > 0);
	ASSERT_EQ(creditObject->getCashCredits(), currentCash + currentBank);
	ASSERT_EQ(creditObject->getBankCredits(), cap);
	creditManagerLogOutput.deleteAll();

	creditObject->addBankCredits(CreditObject::CREDITCAP, false);

	ASSERT_TRUE(creditManagerLogOutput.toString().contains("CREDITCAP"));
	ASSERT_TRUE(stackTraceOutput.length() > 0);
	ASSERT_EQ(creditObject->getCashCredits(), cap);
	ASSERT_EQ(creditObject->getBankCredits(), cap);
	creditManagerLogOutput.deleteAll();
}

TEST_F(CreditObjectTest, TestTransfer) {
	auto currentCash = creditObject->getCashCredits();
	auto currentBank = creditObject->getBankCredits();

	auto tryValidTransfer = [&](int cash, int bank) -> void {
		std::cerr << "[     TEST ] tryValidTransfer(cash=" << cash << ", bank=" << bank << ")" << std::endl;

		creditObject->transferCredits(cash, bank, false);

		ASSERT_TRUE(creditManagerLogOutput.length() == 0);
		ASSERT_TRUE(stackTraceOutput.length() == 0);

		ASSERT_EQ(creditObject->getCashCredits(), cash);
		ASSERT_EQ(creditObject->getBankCredits(), bank);

		currentCash = cash;
		currentBank = bank;

		if (isVerbose) {
			std::cerr << "[     PASS ] currentCash=" << currentCash << "; currentBank=" << currentBank << std::endl;
		}
	};

	auto tryInvalidTransfer = [&](int cash, int bank, String expect = "invalid") -> void {
		std::cerr << "[     TEST ] tryInvalidTransfer(cash=" << cash << ", bank=" << bank << ")" << std::endl;

		creditObject->transferCredits(cash, bank, false);

		ASSERT_TRUE(creditManagerLogOutput.toString().contains(expect));
		ASSERT_TRUE(stackTraceOutput.length() > 0);
		ASSERT_EQ(creditObject->getCashCredits(), currentCash);
		ASSERT_EQ(creditObject->getBankCredits(), currentBank);
		creditManagerLogOutput.deleteAll();

		if (isVerbose) {
			std::cerr << "[     PASS ] currentCash=" << currentCash << "; currentBank=" << currentBank << std::endl;
		}
	};

	tryValidTransfer(currentBank + currentCash, 0);
	tryValidTransfer(startCash, startBank);
	tryValidTransfer(startBank, startCash);

	tryInvalidTransfer(-1 * currentBank, -1 * currentCash);
	tryInvalidTransfer(-1000, -1000);
	tryInvalidTransfer(currentBank + currentCash, -1000);
	tryInvalidTransfer(-1000, currentBank + currentCash);
	tryInvalidTransfer(currentCash, CreditObject::CREDITCAP + 1);
	tryInvalidTransfer(currentBank, currentCash + 1, "unbalanced");
	tryInvalidTransfer(0, 0, "unbalanced");
}
