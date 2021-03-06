#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "MTVector.h"

constexpr uint32_t MONEY_PER_OPERATION = 1000;
constexpr uint32_t N_THREADS = 20;
constexpr uint32_t TOTAL_MONEY = MONEY_PER_OPERATION * N_THREADS;

class Wallet {
private:
    MTVector<int> _money;
public:
    Wallet (){};
    const uint32_t getMoney() {return _money.size();}
    void addMoney(const uint32_t amount) {
        for (uint32_t i = 0; i < amount; i++) {
            _money.push_back(i);
        }
    }
};

uint32_t testWallet() {
    Wallet wallet;
    std::vector<std::thread> threads;
    for (uint32_t i = 0; i < N_THREADS; i++) {
        threads.push_back(std::thread(&Wallet::addMoney, &wallet, MONEY_PER_OPERATION));
    }

    auto range = threads.size();
    for (uint32_t i  = 0; i < range; i++) {
        threads[i].join();
    }

    return wallet.getMoney();
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    uint32_t val = 0;
    for (uint16_t i = 0; i < 1000; i++) {
        val = testWallet();
            if (val != TOTAL_MONEY) {
            std::cout << "Error in Simulation: " << i << ", Money in Wallet" << val << std::endl;
        }
    }

    std::cout << "Simulation Over" << std::endl;
    return 0;
}