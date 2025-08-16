cmake_minimum_required(VERSION 3.10)
project(LiveStrategyBacktester LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define Windows version (Windows 10)
add_definitions(-D_WIN32_WINNT=0x0A00)

find_package(Threads REQUIRED)
include_directories(include)

add_executable(backtester
    src/main.cpp
    src/data_manager.cpp
    src/backtest_engine.cpp
    src/live_engine.cpp
    src/strategy_framework.cpp
    src/performance_analytics.cpp
    src/risk_manager.cpp
    src/order_matching.cpp
    src/market_microstructure.cpp
    src/analytics_ml.cpp
)

target_link_libraries(backtester Threads::Threads)