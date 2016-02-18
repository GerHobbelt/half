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
    cout << typeid(T).name() << " " << sum << " " << diff.count() << endl;
}

int main() {
    FloatVector vct(10000);
    for (auto& value: vct) {
        value = static_cast<float>(rand())/RAND_MAX;
    }

    MulBenchmark<float>(vct);
    MulBenchmark<half_float::half>(vct);

    return 0;
}
