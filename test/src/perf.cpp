#include <cstdlib>

#include <iostream>
#include <vector>
#include <chrono>

#include "include/HalfPrecision.h"

using namespace std;
using namespace std::chrono;

typedef vector<float> FloatVector;

template<typename T>
void MulBenchmark(const FloatVector& vct) {
    const auto begin = high_resolution_clock::now();
    float sum = 0.f;
    for (size_t i = 0; i < vct.size(); ++i) {
        T a = static_cast<T>(vct[i]);
        for (size_t j = 0; j < i; ++j) {
            T b = static_cast<T>(vct[j]);
            sum += a*b;
        }
    }
    duration<float> diff = duration_cast<duration<float>>(high_resolution_clock::now() - begin);
    cout << "Mul: " << typeid(T).name() << " " << sum << " " << diff.count() << endl;
}

void InitVector(FloatVector& vct) {
    for (auto& value: vct) {
        value = static_cast<float>(rand())/RAND_MAX;
    }
}

template<typename T>
void ConversionBenchmark(const FloatVector& src, T& result) {
    const auto begin = high_resolution_clock::now();
    result.resize(src.size());
    for (size_t i = 0; i < src.size(); ++i) {
        result[i] = src[i];
    }
    duration<float> diff = duration_cast<duration<float>>(high_resolution_clock::now() - begin);
    cout << "Conversion: " << typeid(T).name() << " " << diff.count() << endl;
}

int main() {
    FloatVector vct(10000);
    InitVector(vct);

    MulBenchmark<float>(vct);
    MulBenchmark<half_float::half>(vct);

    vct.resize(100000);
    InitVector(vct);
    vector<half_float::half> halfs;
    ConversionBenchmark(vct, halfs);
    vector<float> dummy;
    ConversionBenchmark(vct, dummy);

    return 0;
}
