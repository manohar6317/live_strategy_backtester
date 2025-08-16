#include "backtest_engine.hpp"
#include "data_manager.hpp"
#include "strategy_framework.hpp"
#include <cassert>
#include <iostream>

void test_backtest_engine() {
    DataManager data_manager;
    BacktestEngine engine(data_manager);
    Strategy strategy("TestStrategy", "BTC/USD");
    BacktestConfig config{"2025-01-01", "2025-07-12", 100000.0, "S&P500"};

    data_manager.ingest_historical_data("binance", "BTC/USD");
    engine.run_backtest(strategy, config);

    auto metrics = engine.get_performance_metrics();
    assert(metrics.find("sharpe_ratio") != metrics.end());
    std::cout << "Backtest engine test passed\n";
}

int main() {
    test_backtest_engine();
    return 0;
}