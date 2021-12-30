#include <fstream>
#include <array>
#include <iterator>
#include <vector>
#include <string>

namespace Exporter {
    template <typename T, size_t N>
    void export_array(const std::array<T, N>& arr, std::string path);

    template <typename T, size_t N>
    void import_array(std::array<T, N>& arr, std::string path);
}

template <typename T, size_t N>
void Exporter::export_array(const std::array<T, N>& arr, std::string path) {
    std::ofstream file(path, std::ios::binary);
    if(!file) {
      std::cout << "Cannot open file at " << path << '\n';
      return;
    }
    file.write((char*)arr.data(), N*sizeof(T));
    file.close();
}

template <typename T, size_t N>
void Exporter::import_array(std::array<T, N>& arr, std::string path) {
    std::ifstream file(path, std::ios::binary);
    if(!file) {
      std::cout << "Cannot open file at " << path << '\n';
      return;
    }
    file.read((char*)arr.data(), N*sizeof(T));
    file.close();
    return;
}