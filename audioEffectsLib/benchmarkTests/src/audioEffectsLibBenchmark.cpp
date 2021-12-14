#include <benchmark/benchmark.h>
#include "audioEffects.h"
static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state)
    std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
  audioEffects a;
  float inputBuffer[512] = {};
  float outputBuffer[512] = {};
  for(int x = 0; x < 512; x++)
  {
    inputBuffer[x] = (float)x/512.0;
  }
  for (auto _ : state)
    a.tremoloEffect(inputBuffer, outputBuffer, 512);
}
BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN();
