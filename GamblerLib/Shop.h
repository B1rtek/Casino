#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <iostream>

/**
 * Shop class, represents a shop in which VIPs can purchase and sell items
 */
class Shop {
private:
    std::vector<std::pair<std::string, int>> items;
public:
    Shop() noexcept;

    std::vector<std::pair<std::string, int>> getItems() noexcept { return this->items; }

    void addItem(std::pair<std::string, int> item) noexcept { this->items.push_back(item); }

    void removeItem(std::string itemName) noexcept;

    int findItemValue(std::string itemName) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Shop& shop) noexcept;
};