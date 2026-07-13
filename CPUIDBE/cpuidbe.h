#include <string>
#include <type_traits>

inline std::string ZeroPadNumber(int value, int width) {
    std::string s = std::to_string(value);
    if ((int)s.size() < width) s.insert(0, width - s.size(), '0');
    return s;
}

std::string ZeroPadNumber(int value, int width);

void ZeroPadNumber(int value, int width, std::string &out) {
    out = ZeroPadNumber(value, width);
}

template<typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
std::string ZeroPadNumber(T value, int width) {
    std::string s = std::to_string(value);
    if ((int)s.size() < width) s.insert(0, width - s.size(), '0');
    return s;
}
