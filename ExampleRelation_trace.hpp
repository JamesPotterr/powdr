
// AUTOGENERATED FILE

#include "barretenberg/ecc/curves/bn254/fr.hpp"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <vector>


using namespace barretenberg;
using fr = barretenberg::fr;

using Row = ExampleRelation::ExampleRelationRow<barretenberg::fr>;
fr read_field(std::ifstream& file)
{
    uint8_t buffer[32];
    file.read(reinterpret_cast<char*>(buffer), 32);

    // swap it to big endian ???? TODO: create utility
    for (int n = 0, m = 31; n < m; ++n, --m) {
        std::swap(buffer[n], buffer[m]);
    }

    return fr::serialize_from_buffer(buffer);
}
    
std::vector<Row> read_both_file_into_cols(
    std::string commited_filename,
    std::string constants_filename,
) {
    std::vector<Row> rows;

    // open both files
    std::ifstream commited_file(commited_filename, std::ios::binary);
    if (!commited_file) {
        std::cout << 'Error opening commited file' << std::endl;
        return {};
    }

    std::ifstream constant_file(constant_filename, std::ios::binary);
    if (!constant_file) {
        std::cout << 'Error opening constant file' << std::endl;
        return {};
    }

    // We are assuming that the two files are the same length
    while (commited_file) {
        Row current_row = {};

        current_row.Fibonacci.ISLAST = read_file(constants_filename);
        
        current_row.Fibonacci_x = read_file(commited_filename);
        current_row.Fibonacci_x_shift = read_file(constants_filename);

        current_row.Fibonacci_y = read_file(commited_filename);
        current_row.Fibonacci_y_shift = read_file(constants_filename);

        rows.push_back(current_row);
    }

    return rows;
}
    