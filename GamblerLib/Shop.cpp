#include "Shop.h"

Shop::Shop() noexcept {
    this->items = { 
        {"Yacht",     50000},
        {"Car",       20000},
        {"Apartment", 100000},
        {"Motor",     5000} 
    };
}

void Shop::removeItem(std::string itemName) noexcept {
    for (int i = 0; i < this->items.size(); i++) {
        if (this->items[i].first == itemName) {
            this->items.erase(items.begin() + i);
            return;
        }
    }
}

int Shop::findItemValue(std::string itemName) noexcept {
    for (int i = 0; i < this->items.size(); i++) {
        if (this->items[i].first == itemName) return this->items[i].second;
    }
    return 0;
}

std::ostream& operator<<(std::ostream& os, Shop& shop) noexcept {
    for (int i = 0; i < shop.getItems().size(); i++)
        os << shop.getItems()[i].first << " " << shop.getItems()[i].second << std::endl;
    return os;
}