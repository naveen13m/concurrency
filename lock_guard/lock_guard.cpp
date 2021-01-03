#include <thread>
#include <mutex>

uint counter = 0;
constexpr uint thread_count_limit = 1e5;
std::mutex mtx;

void increment_counter() {
    std::lock_guard<std::mutex> lg(mtx);
    for (uint i = 0; i < thread_count_limit; i++) {
        counter++;
    }
}

int main() {
    std::thread T1(increment_counter);
    std::thread T2(increment_counter);

    T1.join();
    T2.join();

    printf("Expected = %d, Actual = %d, Error = %d\n", 
        2 * thread_count_limit, counter, 2 * thread_count_limit - counter);

    return 0;
}