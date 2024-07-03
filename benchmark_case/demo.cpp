#include <benchmark/benchmark.h>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <numeric>
#include <vector>
#include <iostream>



// // // 数组（使用 std::vector 模拟动态数组）
// static void BM_Array_Insert(benchmark::State& state) {
//     for (auto _ : state) {
//         std::vector<int> arr;
//         for (int i = 0; i < state.range(0); ++i) {
//             arr.push_back(i);
//         }
//     }
// }
// BENCHMARK(BM_Array_Insert)->Iterations(100);

// static void BM_Array_Access(benchmark::State& state) {
    
//     // 初始化数组
//     std::vector<int> arr;
//     for (int i = 0; i < 5000; ++i) {
//         arr.push_back(i);
//     }
//     for (auto _ : state) {
//         for (int i = 0; i <  state.range(0); ++i) {
//             benchmark::DoNotOptimize(arr[i]);
//         }
//     }
// }
// BENCHMARK(BM_Array_Access)->Iterations(100);

// // // 哈希表
// static void BM_HashMap_Insert(benchmark::State& state) {
//     for (auto _ : state) {
//         std::unordered_map<int, int> x_map;
//         for (int i = 0; i < 5000; ++i) {
//             x_map[i] = i;
//         }
//     }
// }
// BENCHMARK(BM_HashMap_Insert)->Iterations(100);

// static void BM_HashMap_Lookup(benchmark::State& state) {
//     std::unordered_map<int, int> x_map;
//     for (int i = 0; i < 5000; ++i) {
//         x_map[i] = i;
//     }
//     for (auto _ : state) {
//         for (int i = 0; i < 5000; ++i) {
//             benchmark::DoNotOptimize(x_map.find(i));
//         }
//     }
// }
// BENCHMARK(BM_HashMap_Lookup)->Iterations(100);

// void test_vector_insert(std::vector<int>& vec)
// {
//     vec.emplace_back(0);
// }

// void BM_test_vector_insert(benchmark::State& state)
// {
//     std::vector<int> vec;
//     vec.reserve(10000);

//     for(const auto& _ : state)
//     {
//         test_vector_insert(vec);
//     }
// }
// BENCHMARK(BM_test_vector_insert)->Iterations(5000);

// void test_hashmap_insert(std::unordered_map<int, int>& hashmap)
// {
//     hashmap[0] = 0;
// }
// void BM_hashmap_insert(benchmark::State& state)
// {
//     std::unordered_map<int, int> hashmap;
//     hashmap.reserve(10000);
//     for(const auto& _ : state)
//     {
//         test_hashmap_insert(hashmap);
//     }
// }


// BENCHMARK(BM_hashmap_insert)->Iterations(5000);

// template <typename T, bool is_reserve = true>
// void bench_vector_reserve(benchmark::State& state)
// {
// 	for (auto _ : state) {
// 		std::vector<T> container;
// 		if constexpr (is_reserve) {
//             // 通过range方法获取传入的参数
// 			container.reserve(state.range(0));
// 		}
// 		for (std::size_t i = 0; i < state.range(0); ++i) {
//             // std::cout << i << std::endl;
// 			container.push_back(T{});
// 		}
// 	}
// }


// // Range 循环次数
// // RangeMultiplier 倍数测试
// BENCHMARK_TEMPLATE(bench_vector_reserve, std::string)->RangeMultiplier(10)->Range(1, 100);
// // BENCHMARK_TEMPLATE(bench_vector_reserve, std::string, false)->RangeMultiplier(10)->Range(1, 10)->Iterations(1);





void BM_bench_inner_product(benchmark::State& state)
{
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};

    for(const auto& _ : state)
    {
         int result = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0);
    }
}

BENCHMARK(BM_bench_inner_product)->Iterations(1000);


void BM_bench_inner_product_double(benchmark::State& state)
{
    std::vector<double> v1 = {0.1, 0.2, 0.3,0.1, 0.2, 0.3,0.1, 0.2, 0.3,0.1, 0.2, 0.3};
    std::vector<double> v2 = {0.4, 0.5, 0.6};

    for(const auto& _ : state)
    {
         int result = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0);
    }
}


BENCHMARK(BM_bench_inner_product_double)->Iterations(1000);



BENCHMARK_MAIN();