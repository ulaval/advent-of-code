// AoC 2020-10

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>

int main(int argc, char* argv[])
{
    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    assert(input_file.is_open());
    
    std::vector<unsigned> jolts;
    std::copy(std::istream_iterator<int>{input_file}, std::istream_iterator<int>{}, std::back_inserter(jolts));

    // Part 1
    std::vector<int> diffs(4);
    jolts.push_back(0);
    std::sort(jolts.begin(), jolts.end());
    jolts.push_back(*std::prev(jolts.end())+3);
    for (auto it = std::next(jolts.cbegin()); it != jolts.cend(); it++)
        diffs[*it - *std::prev(it)]++;
    std::cout << "Part 1 answer = " << diffs[1] * diffs[3] << '\n';

    // Part 2
    std::vector<long> paths(jolts.size(), 0);
    paths[0]=1;
    for (int i = 1; i < jolts.size(); i++) {
        for (int j=0; j < i; j++) {
            if (jolts[j]+3 >= jolts[i])
                paths[i] += paths[j];
        }
    }
    std::cout << "Part 2 answer = " << paths[jolts.size()-1] << '\n';
}
