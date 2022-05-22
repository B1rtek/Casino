include "pch.h"
#include "CppUnitTest.h"
#include "../Players/Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlayerUnitTest
{
	TEST_CLASS(PlayerUnitTest)
	{
	public:

		TEST_METHOD(TestPlayerCreateEmpty)
		{
			Player gracz;
			Assert::AreEqual("Player", gracz.getName().c_str());
			Assert::AreEqual(0, gracz.getBalance(), 0.01);
		}

		TEST_METHOD(TestPlayerCreateOnlyName)
		{
			Player gracz("Kamil");
			Assert::AreEqual(gracz.getName().c_str(), "Kamil");
			Assert::AreEqual(gracz.getBalance(), 0, 0.01);
			Assert::IsTrue(gracz.getDeposits().empty());
		}

		TEST_METHOD(TestPlayerCreate)
		{
			Player gracz("Kamil", 5.50);
			Assert::AreEqual(gracz.getName().c_str(), "Kamil");
			Assert::AreEqual(gracz.getBalance(), 5.5, 0.01);
			Assert::AreEqual(gracz.getDeposits()[0], 5.5, 0.01);
		}

		TEST_METHOD(TestPlayerChangeName)
		{
			Player gracz("Kamil", 5.50);
			gracz.changeName("Piotrek");
			Assert::AreEqual(gracz.getName().c_str(), "Piotrek");
		}

		TEST_METHOD(TestPlayerDepositBalanceToEmptyAcc)
		{
			Player gracz("Kamil");
			gracz.depositBalance(2.22);
			Assert::AreEqual(gracz.getBalance(), 2.22, 0.01);
			Assert::AreEqual(gracz.getDeposits()[0], 2.22, 0.01);
		}

		TEST_METHOD(TestPlayerDepositBalance)
		{
			Player gracz("Kamil", 5.50);
			gracz.depositBalance(2.22);
			Assert::AreEqual(gracz.getBalance(), 7.72, 0.01);
			Assert::AreEqual(gracz.getDeposits()[0], 5.50, 0.01);
			Assert::AreEqual(gracz.getDeposits()[1], 2.22, 0.01);
		}

		TEST_METHOD(TestPlayerWithdrawBalance)
		{
			Player gracz("Kamil", 5.50);
			gracz.withdrawBalance(2.20);
			Assert::AreEqual(gracz.getBalance(), 3.30, 0.01);
			Assert::AreEqual(gracz.getWithdrawals()[0], 2.20, 0.01);
		}

		TEST_METHOD(TestPlayerWithdrawTooManyBalance)
		{
			Player gracz("Kamil", 5.50);
			gracz.withdrawBalance(20.11);
			Assert::AreEqual(gracz.getBalance(), 5.50, 0.01);
			Assert::IsTrue(gracz.getWithdrawals().empty());
		}

		TEST_METHOD(TestPlayerALotTransactions)
		{
			Player gracz("Kamil", 5.50);
			gracz.depositBalance(2.10);
			gracz.withdrawBalance(3.10);
			gracz.depositBalance(8.50);
			gracz.withdrawBalance(5.50);

			Assert::AreEqual(gracz.totalDeposited(), 16.10, 0.01);
			Assert::AreEqual(gracz.totalWithdrawed(), 8.60, 0.01);
			Assert::AreEqual(gracz.totalProfit(), -7.50, 0.01);
		}

		TEST_METHOD(TestGuestCreate)
		{
			Guest gosc("Kamil", 5.5);
			Assert::AreEqual("Kamil", gosc.getName().c_str());
			Assert::AreEqual(5.5, gosc.getBalance(), 0.01);

			Guest gosc2;
			Assert::AreEqual("Player", gosc2.getName().c_str());
			Assert::AreEqual(0, gosc2.getBalance(), 0.01);
		}

		TEST_METHOD(TestGuestDepositWithdrawTooMany)
		{
			Guest gosc("Kamil", 1500);
			gosc.depositBalance(110000);
			Assert::AreEqual(1500, gosc.getBalance(), 0.01);
			gosc.withdrawBalance(1200);
			Assert::AreEqual(1500, gosc.getBalance(), 0.01);
		}

		TEST_METHOD(TestVIPCheckPlayerBalance)
		{
			Guest gosc("Kamil", 150);
			VIP vip("Elon", 25000);
			Assert::AreEqual(150, vip.checkPlayerBalance(gosc), 0.01);
		}

		TEST_METHOD(TestVIPUsingSafe)
		{
			VIP vip("Elon", 25000);
			vip.depositToSafe(1000);
			vip.withdrawFromSafe(200);
			Assert::AreEqual(24200, vip.getBalance(), 0.01);
			Assert::AreEqual(800, vip.getSafeValue(), 0.01);
		}

		TEST_METHOD(TestVIPResetStats)
		{
			VIP vip("Elon", 25000);
			vip.depositBalance(100);
			vip.withdrawBalance(200);
			vip.depositBalance(300);
			vip.withdrawBalance(400);
			vip.resetStats();
			Assert::IsTrue(vip.getDeposits().empty());
			Assert::IsTrue(vip.getWithdrawals().empty());
		}

		TEST_METHOD(TestShopRemoveItem)
		{
			Shop shop;
			shop.removeItem("Yacht");
			Assert::AreEqual(shop.getItems()[0].first.c_str(), "Car");
		}
	};
}