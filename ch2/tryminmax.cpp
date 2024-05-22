#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main(){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto min_max = std::minmax_element(v.begin(), v.end(), [](const int &a, const int &b) { return a > b; });
    std::cout << "min: " << *min_max.first << ", max: " << *min_max.second << endl;
    return 0;
}