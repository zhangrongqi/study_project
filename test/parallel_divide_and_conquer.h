#pragma once
#include <iostream>
#include <vector>
#include <future>
#include <cmath>
#include <stdexcept>

namespace parallel_divide_and_conquer
{
    // ͳ�����ݿ�Ľṹ��
    struct Stats {
        double sum = 0.0;
        double sum_sq = 0.0;
        size_t count = 0;
    };

    // �������ݿ��ͳ����Ϣ
    Stats compute_block(const std::vector<double>& data, size_t start, size_t end) {
        double sum = 0.0;
        double sum_sq = 0.0;
        for (size_t i = start; i < end; ++i) {
            sum += data[i];
            sum_sq += data[i] * data[i];
        }
        return { sum, sum_sq, end - start };
    }

    // �ϲ�����ͳ�ƽ��
    Stats combine(const Stats& a, const Stats& b) {
        return {
            a.sum + b.sum,
            a.sum_sq + b.sum_sq,
            a.count + b.count
        };
    }

    // ���з��εݹ����
    Stats parallel_divide_and_conquer(const std::vector<double>& data,
        size_t start,
        size_t end,
        size_t threshold = 10000) {
        if (end - start <= threshold) {
            return compute_block(data, start, end);
        }
        else {
            size_t mid = start + (end - start) / 2;

            // �첽��������������
            auto left_future = std::async(std::launch::async,
                parallel_divide_and_conquer, std::cref(data), start, mid, threshold);
            auto right_future = std::async(std::launch::async,
                parallel_divide_and_conquer, std::cref(data), mid, end, threshold);

            // ��ȡ���ϲ����
            return combine(left_future.get(), right_future.get());
        }
    }

    // �����̳߳ؼ����̹߳�����
    //Stats parallel_divide_and_conquer(const std::vector<double>& data,
    //    size_t start,
    //    size_t end,
    //    size_t threshold = 10000) {
    //    if (end - start <= threshold) {
    //        return compute_block(data, start, end);
    //    }
    //    else {
    //        size_t mid = start + (end - start) / 2;

    //        // �첽��������������
    //        auto left_future = std::async(std::launch::async,
    //            parallel_divide_and_conquer, std::cref(data), start, mid, threshold);
    //        auto right_future = parallel_divide_and_conquer(data, mid, end, threshold);

    //        // ��ȡ���ϲ����
    //        return combine(left_future.get(), right_future);
    //    }
    //}

    // ������㺯��
    double calculate_variance(const Stats& s) {
        if (s.count == 0) {
            throw std::invalid_argument("Cannot compute variance of empty dataset");
        }
        double mean = s.sum / s.count;
        return (s.sum_sq / s.count) - (mean * mean);
    }

    //int main() {
    //    // ʾ�����ݣ����滻Ϊʵ�����ݣ�
    //    std::vector<double> data(1000000, 1.0);  // 100���1.0������

    //    try {
    //        // ִ�в��м���
    //        Stats result = parallel_divide_and_conquer(data, 0, data.size());

    //        // ���㲢�������
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