#include "Benchmarking.h"

#include <fmt/color.h>
#include <utility>

namespace Benchmark {

ScopedTimer::ScopedTimer(std::string &&name)
    : m_name(std::move(name))
{
    m_start = std::chrono::high_resolution_clock::now();
}

ScopedTimer::~ScopedTimer()
{
    // Print time in both milliseconds and nanoseconds.
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_start);
    fmt::print(fg(fmt::color::magenta), "[Benchmark] {} took {:.2f} ms ({} ns)\n", m_name,
               static_cast<double>(duration.count()) / 1000000.0f,
               duration.count());
}

} // namespace Benchmark
