#include <iostream>
#include <vector>
#include <algorithm>

struct Order {
    int64_t user_id;
    int64_t amount;
    int64_t price;
    bool side; // true for buy, false for sell

    Order(int64_t uid, int64_t amt, int64_t prc, bool sd)
        : user_id(uid), amount(amt), price(prc), side(sd) {}
};

struct BalanceChange {
    int64_t user_id;
    int64_t value;
    std::string currency;

    BalanceChange(int64_t uid, int64_t val, const std::string& curr)
        : user_id(uid), value(val), currency(curr) {}
};

class OrderBook {
private:
    std::vector<Order> sell_orders; // Sell orders sorted by price ascending
    std::vector<Order> buy_orders;  // Buy orders sorted by price descending

public:
    void add_order(const Order& order) {
        if (order.side) { // Buy order
            buy_orders.push_back(order);
            std::sort(buy_orders.begin(), buy_orders.end(), [](const Order& a, const Order& b) {
                return a.price > b.price;
                });
        }
        else { // Sell order
            sell_orders.push_back(order);
            std::sort(sell_orders.begin(), sell_orders.end(), [](const Order& a, const Order& b) {
                return a.price < b.price;
                });
        }
        match_orders();
    }

private:
    void match_orders() {
        while (!sell_orders.empty() && !buy_orders.empty() && sell_orders.front().price <= buy_orders.front().price) {
            Order& sell_order = sell_orders.front();
            Order& buy_order = buy_orders.front();

            // Determine the amount to be traded
            int64_t traded_amount = std::min(sell_order.amount, buy_order.amount);
            int64_t traded_price = sell_order.price;

            // Update the orders and balance changes
            sell_order.amount -= traded_amount;
            buy_order.amount -= traded_amount;

            // Output balance changes
            std::cout << BalanceChange(sell_order.user_id, -traded_amount, "UAH").value << " " << BalanceChange(sell_order.user_id, -traded_amount, "UAH").currency << "\n";
            std::cout << BalanceChange(sell_order.user_id, traded_amount * traded_price, "USD").value << " " << BalanceChange(sell_order.user_id, traded_amount * traded_price, "USD").currency << "\n";
            std::cout << BalanceChange(buy_order.user_id, traded_amount, "UAH").value << " " << BalanceChange(buy_order.user_id, traded_amount, "UAH").currency << "\n";
            std::cout << BalanceChange(buy_order.user_id, -traded_amount * traded_price, "USD").value << " " << BalanceChange(buy_order.user_id, -traded_amount * traded_price, "USD").currency << "\n";

            // Remove fully matched orders
            if (sell_order.amount == 0) {
                sell_orders.erase(sell_orders.begin());
            }
            if (buy_order.amount == 0) {
                buy_orders.erase(buy_orders.begin());
            }
        }
    }
};

int main() {
    OrderBook order_book;
    order_book.add_order(Order(1, 100, 27, false)); // Sell order
    order_book.add_order(Order(2, 50, 27, true));   // Buy order

    // Example of taking input from the user
    int64_t user_id, amount, price;
    bool side;
    std::cout << "Enter order details (user_id amount price side): ";
    while (std::cin >> user_id >> amount >> price >> side) {
        order_book.add_order(Order(user_id, amount, price, side));
        std::cout << "Enter order details (user_id amount price side): ";
    }

    return 0;
}
