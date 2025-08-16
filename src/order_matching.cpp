// order_matching.cpp: Implementation of OrderMatchingEngine class for processing trade orders
// Purpose: Matches orders with market data and applies realistic trading effects (slippage, latency)
// for the BTC/USDT trading system, supporting the MovingAverage strategy

#include "order_matching.hpp"  // Header file defining OrderMatchingEngine class
#include <iostream>           // For console output (logging order matching and effects)

// Match an order against current market data
// order: Order struct containing asset, price, volume, type (BUY/SELL/HOLD), timestamp
// market_data: MarketData struct with bid, ask, volume, and timestamp
// Why: Simulates trade execution by matching orders to market conditions
// Note: Placeholder implementation; needs actual matching logic
void OrderMatchingEngine::match_order(const Order& order, const MarketData& market_data) {
    // Log order details for debugging and user feedback
    std::cout << "Matching order for " << order.asset << "\n";
    
    // Log order price and market bid/ask prices for comparison
    std::cout << "Order price: " << order.price << ", Market bid: " << market_data.bid
              << ", Market ask: " << market_data.ask << "\n";
    
    // Log successful match; actual logic missing
    // Bug: Placeholder; should check if order price is executable (e.g., BUY at or below ask)
    std::cout << "Order matched\n";
}

// Apply slippage and latency effects to an order
// order: Order struct to be modified
// Why: Simulates realistic trade execution costs and delays for BTC/USDT trades
// Note: Simplistic implementation with fixed 0.1% slippage
void OrderMatchingEngine::apply_slippage_and_latency(Order& order) const {
    // Apply 0.1% slippage by increasing order price
    // Why: Simulates market impact and execution delay
    // Bug: Fixed slippage; should vary based on market conditions (e.g., volume, volatility)
    order.price *= 1.001; // Simulate 0.1% slippage
    
    // Log application of effects for debugging
    std::cout << "Applied slippage and latency to order\n";
}