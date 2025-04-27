#pragma once
#include <iostream>
#include <vector>
#include <future>
#include <cmath>
#include <stdexcept>

namespace parallel_divide_and_conquer
{
    // 统计数据块的结构体
    struct Stats {
        double sum = 0.0;
        double sum_sq = 0.0;
        size_t count = 0;
    };

    // 计算数据块的统计信息
    Stats compute_block(const std::vector<double>& data, size_t start, size_t end) {
        double sum = 0.0;
        double sum_sq = 0.0;
        for (size_t i = start; i < end; ++i) {
            sum += data[i];
            sum_sq += data[i] * data[i];
        }
        return { sum, sum_sq, end - start };
    }

    // 合并两个统计结果
    Stats combine(const Stats& a, const Stats& b) {
        return {
            a.sum + b.sum,
            a.sum_sq + b.sum_sq,
            a.count + b.count
        };
    }

    // 并行分治递归计算
    Stats parallel_divide_and_conquer(const std::vector<double>& data,
        size_t start,
        size_t end,
        size_t threshold = 10000) {
        if (end - start <= threshold) {
            return compute_block(data, start, end);
        }
        else {
            size_t mid = start + (end - start) / 2;

            // 异步处理左右两部分
            auto left_future = std::async(std::launch::async,
                parallel_divide_and_conquer, std::cref(data), start, mid, threshold);
            auto right_future = std::async(std::launch::async,
                parallel_divide_and_conquer, std::cref(data), mid, end, threshold);

            // 获取并合并结果
            return combine(left_future.get(), right_future.get());
        }
    }

    // 不如线程池减少线程管理开销
    //Stats parallel_divide_and_conquer(const std::vector<double>& data,
    //    size_t start,
    //    size_t end,
    //    size_t threshold = 10000) {
    //    if (end - start <= threshold) {
    //        return compute_block(data, start, end);
    //    }
    //    else {
    //        size_t mid = start + (end - start) / 2;

    //        // 异步处理左右两部分
    //        auto left_future = std::async(std::launch::async,
    //            parallel_divide_and_conquer, std::cref(data), start, mid, threshold);
    //        auto right_future = parallel_divide_and_conquer(data, mid, end, threshold);

    //        // 获取并合并结果
    //        return combine(left_future.get(), right_future);
    //    }
    //}

    // 方差计算函数
    double calculate_variance(const Stats& s) {
        if (s.count == 0) {
            throw std::invalid_argument("Cannot compute variance of empty dataset");
        }
        double mean = s.sum / s.count;
        return (s.sum_sq / s.count) - (mean * mean);
    }

    //int main() {
    //    // 示例数据（可替换为实际数据）
    //    std::vector<double> data(1000000, 1.0);  // 100万个1.0的数据

    //    try {
    //        // 执行并行计算
    //        Stats result = parallel_divide_and_conquer(data, 0, data.size());

    //        // 计算并输出方差
    //        double variance = calculate_variance(result);
    //        std::cout << "Calculated Variance: " << variance << std::endl;
    //        std::cout << "Expected Variance: 0.0" << std::endl;
    //    }
    //    catch (const std::exception& e) {
    //        std::cerr << "Error: " << e.what() << std::endl;
    //        return 1;
    //    }

    //    return 0;
    //}
}