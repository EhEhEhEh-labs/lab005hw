#include "Transaction.h"
#include "Account.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>


class AccountMock : public Account {
public:
	AccountMock(int id, int balance) : Account(id, balance) {}
	MOCK_CONST_METHOD0(GetBalance, int());
	MOCK_METHOD1(ChangeBalance, void(int diff));
	MOCK_METHOD0(Lock, void());
	MOCK_METHOD0(Unlock, void());
};
class TransactionMock : public Transaction {
public:
	MOCK_METHOD3(Make, bool(Account& from, Account& to, int sum));
};

TEST(Account, Mock) {
	AccountMock ac(1, 100);
	EXPECT_CALL(ac, GetBalance()).Times(1);
	EXPECT_CALL(ac, ChangeBalance(testing::_)).Times(1);
	EXPECT_CALL(ac, Lock()).Times(1);
	EXPECT_CALL(ac, Unlock()).Times(1);
	ac.GetBalance();
	ac.ChangeBalance(20);
	ac.Lock();
	ac.Unlock();
}

TEST(Account, Init) {
    AccountMock ac(1, 1000);
    EXPECT_EQ(ac.id(), 1);
    EXPECT_EQ(1000, ac.Account::GetBalance());
}

TEST(Account, GetBalance) {
    AccountMock ac(1, 1000);
    EXPECT_EQ(1000, ac.Account::GetBalance());
}

TEST(Account, ChangeBalance) {
    AccountMock ac(1, 1000);
    ac.Account::Lock();
    ac.Account::ChangeBalance(100);
    EXPECT_NO_THROW(ac.Account::Unlock());
    EXPECT_EQ(1100, ac.Account::GetBalance());
}

TEST(Account, Lock) {
    AccountMock ac(1, 100);
    EXPECT_THROW(ac.Account::ChangeBalance(100), std::runtime_error);
}

TEST(Account, Unlock) {
    AccountMock ac(1, 100);
    EXPECT_NO_THROW(ac.Account::Unlock());
}

TEST(Transaction, Mock) {
	TransactionMock tr;
	Account ac1(1, 50);
	Account ac2(2, 500);
	EXPECT_CALL(tr, Make(testing::_, testing::_, testing::_)).Times(1);
	tr.Make(ac1, ac2, 199);
}

TEST(Transaction, Make) {
    Transaction tr;
    Account ac1(1, 200);
    Account ac2(1, 200);
    Account ac3(2, 200);
    EXPECT_THROW(tr.Make(ac1, ac2, 150), std::logic_error);
    EXPECT_THROW(tr.Make(ac1, ac3, -10), std::invalid_argument);
    EXPECT_THROW(tr.Make(ac1, ac2, 99), std::logic_error);
    EXPECT_EQ(tr.fee() * 2 > 150, false);
}

TEST(Transaction, SaveToDataBase) {
    Transaction tr;
    Account ac1(1, 2000);
    Account ac2(2, 200);
    tr.set_fee(0);
    tr.Make(ac1, ac2, 400);
    EXPECT_EQ(ac1.GetBalance(), 1600);
    EXPECT_EQ(ac2.GetBalance(), 600);
}
