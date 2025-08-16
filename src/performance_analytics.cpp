// performance_analytics.cpp: Implementation of PerformanceAnalytics class for evaluating trading performance
// Purpose: Calculates and compares performance metrics (Sharpe, Sortino, MaxDD) for trades generated
// by the BTC/USDT trading system, supporting analysis of the MovingAverage strategy

#include "performance_analytics.hpp"  // Header file defining PerformanceAnalytics class
#include <iostream>                  // For console output (logging metrics and errors)
#include <numeric>                   // For std::accumulate to compute mean returns
#include <cmath>                     // For std::sqrt to calculate standard deviation

// Calculate performance metrics for a set of trades
// trades: Vector of Trade structs from backtesting or live trading
// Why: Evaluates strategy performance using metrics like Sharpe, Sortino, and Maximum Drawdown
void PerformanceAnalytics::calculate_metrics(const std::vector<Trade>& trades) {
    // Check if trades vector is empty to avoid invalid calculations
    if (trades.empty()) {
        std::cout << "No trades to analyze\n";
        return;
    }
    
    // Calculate returns as percentage change between consecutive trade prices
    std::vector<double> returns;
    for (auto it = trades.begin() + 1; it != trades.end(); ++it) {
        double prev_price = (it - 1)->price;  // Previous trade price
        double curr_price = it->price;         // Current trade price
        // Compute return as (current - previous) / previous
        returns.push_back((curr_price - prev_price) / prev_price);
    }
    
    // Calculate mean return across all trades
    // Why: Used as numerator for Sharpe and Sortino ratios
    double mean_return = std::accumulate(returns.begin(), returns.end(), 0.0) / returns.size();
    
    // Calculate variance of returns
    double variance = 0.0;
    for (const auto& ret : returns) {
        // Sum squared differences from mean return
        variance += (ret - mean_return) * (ret - mean_return);
    }
    variance /= returns.size();  // Average to get variance
    
    // Calculate standard deviation as square root of variance
    double std_dev = std::sqrt(variance);
    
    // Compute Sharpe ratio: mean return divided by standard deviation
    // Why: Measures risk-adjusted return for the strategy
    metrics_["Sharpe"] = mean_return / std_dev;
    
    // Compute Sortino ratio: mean return divided by standard deviation (simplified)
    // Note: Placeholder; Sortino should use downside deviation, needs fix
    metrics_["Sortino"] = mean_return / std_dev; // Simplified
    
    // Set Maximum Drawdown (MaxDD) as placeholder value
    // Note: Placeholder; should calculate actual peak-to-trough loss
    metrics_["MaxDD"] = 0.1; // Placeholder
    
    // Log calculated metrics for debugging and user feedback
    std::cout << "Calculated performance metrics: Sharpe=" << metrics_["Sharpe"]
              << ", Sortino=" << metrics_["Sortino"] << ", MaxDD=" << metrics_["MaxDD"] << "\n";
}

// Compare performance of live trades against backtest trades
// live_trades: Trades from live shadow trading
// backtest_trades: Trades from backtesting
// Why: Evaluates consistency between live and historical performance
// Note: Placeholder implementation; needs logic to compare metrics
void PerformanceAnalytics::compare_live_vs_backtest(const std::vector<Trade>& live_trades, const std::vector<Trade>& backtest_trades) {
    // Log comparison process for debugging
    std::cout << "Comparing live vs backtest performance...\n";
}

// Retrieve calculated performance metrics
// Returns: Map of metric names to values (e.g., Sharpe, Sortino, MaxDD)
// Why: Provides access to metrics for reporting or further analysis
std::map<std::string, double> PerformanceAnalytics::get_metrics() const {
    return metrics_; // Return stored metrics
}