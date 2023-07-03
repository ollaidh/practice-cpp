// ATM machine that stores banknotes of 5 denominations: 20, 50, 100, 200, and 500 dollars. Initially the ATM is empty.
// The user can use the machine to deposit or withdraw any amount of money.
// When withdrawing, the machine prioritizes using banknotes of larger values (Leetcode Mode) -
// try to withdraw $600 and there are 3 $200 banknotes and 1 $500 banknote, then the withdraw request will be rejected
// because the machine will first try to use the $500 banknote and then be unable to use banknotes to complete the
// remaining $100. Note that the machine is not allowed to use the $200 banknotes instead of the $500 banknote.

#include <vector>
#include <map>
#include <algorithm>

#include <gtest/gtest.h>


class ATM {
public:
    ATM() {
        banknotes = {{20, 0}, {50, 0}, {100, 0}, {200, 0}, {500, 0}};
    }

    void deposit(const std::vector<int>& banknotesCount) {
        int i = 0;
        for (auto const& [key, val] : banknotes) {
            banknotes[key] = val + banknotesCount[i];
            i++;
        }
    }

    void updateBanknotesAmount(const std::vector<int>& banknotesToWithdraw) {
        int i = 0;
        for (auto const& [key, val] : banknotes) {
            banknotes[key] = val - banknotesToWithdraw[i];
            i++;
        }
    }

    std::vector<int> withdraw(int amount) {
        std::vector<int> withdrBanknotes = {0, 0, 0, 0, 0};
        int64_t remaining = amount;
        int i = banknotes.size() - 1;
        for (auto iter = banknotes.rbegin(); iter != banknotes.rend(); ++iter) {
            int64_t currency = iter->first;
            int64_t currAmount = iter->second;
            if (currency > remaining) {
                i--;
                continue;
            }
            int withdrawBanknotes = std::min(currAmount, remaining / currency);
            remaining -= withdrawBanknotes * currency;
            withdrBanknotes[i] += withdrawBanknotes;

            if (remaining == 0) {
                updateBanknotesAmount(withdrBanknotes);
                return withdrBanknotes;
            }
            i--;
        }
        return {-1};
    }

private:
    std::map<int, int64_t> banknotes;
};

TEST(atm, withdrawalOk) {
    ATM atm;
    atm.deposit({0, 0, 1, 2, 1});

    {
        std::vector<int> result = {0, 0, 1, 0, 1};
        ASSERT_EQ(result, atm.withdraw(600));
    }

    atm.deposit({0, 1, 0, 1, 1});

    {
        std::vector<int> result = {-1};
        ASSERT_EQ(result, atm.withdraw(600));
    }

    {
        std::vector<int> result = {0, 1, 0, 0, 1};
        ASSERT_EQ(result, atm.withdraw(550));
    }
}

TEST(atm, withdrawalBad) {
    ATM atm;
    atm.deposit({0, 0, 0, 3, 1});

    {
        std::vector<int> result = {-1};
        ASSERT_EQ(result, atm.withdraw(600));
    }
}

TEST(atm, withdrawal1) {
    ATM atm;
    atm.deposit({0, 10, 0, 3, 0});

    {
        std::vector<int> result = {0, 2, 0, 2, 0};
        ASSERT_EQ(result, atm.withdraw(500));
    }
}
