#ifndef AOC_HEADER
#define AOC_HEADER

namespace aoc
{
    std::string slurp_file(std::string_view path) {
        std::ios::sync_with_stdio(false);

        std::ifstream is{path.data(), std::ios::in | std::ios::binary};
        is.exceptions(std::ifstream::badbit);

        std::string data;
        for (std::array<char, 256> buffer; is;) {
            is.read(buffer.data(), buffer.size());
            std::ranges::copy(buffer | std::views::take(is.gcount()), std::back_inserter(data));
        }
        return data;
    }

    std::vector<std::string> slurp_lines(std::string_view path) {
        std::vector<std::string> lines;
        {
            std::istringstream is{slurp_file(path)};
            for (std::string line; std::getline(is, line);) {
                lines.push_back(line);
            }
            if (not is and not is.eof()) {
                throw std::runtime_error("input is invalid");
            }
            if (lines.empty()) {
                throw std::runtime_error("input is empty");
            }
            return lines;
        }
    }
}



#endif