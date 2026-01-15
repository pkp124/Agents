#include "mathutils/statistics.hpp"
#include <algorithm>
#include <numeric>

namespace mathutils {

std::optional<double> Statistics::mean(const std::vector<double>& data) {
    // REQ-0005: Empty dataset shall return nullopt
    if (data.empty()) {
        return std::nullopt;
    }
    return sum(data) / static_cast<double>(data.size());
}

double Statistics::sum(const std::vector<double>& data) noexcept {
    return std::accumulate(data.begin(), data.end(), 0.0);
}

std::optional<double> Statistics::min(const std::vector<double>& data) {
    // REQ-0005: Empty dataset shall return nullopt
    if (data.empty()) {
        return std::nullopt;
    }
    return *std::min_element(data.begin(), data.end());
}

std::optional<double> Statistics::max(const std::vector<double>& data) {
    // REQ-0005: Empty dataset shall return nullopt
    if (data.empty()) {
        return std::nullopt;
    }
    return *std::max_element(data.begin(), data.end());
}

std::optional<double> Statistics::range(const std::vector<double>& data) {
    // REQ-0005: Empty dataset shall return nullopt
    auto min_val = min(data);
    auto max_val = max(data);
    
    if (!min_val || !max_val) {
        return std::nullopt;
    }
    
    return *max_val - *min_val;
}

} // namespace mathutils
