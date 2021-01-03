#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

class Barrier {
public:
    Barrier(uint max_count) : max_count_(max_count) {}

    void wait() {
        std::unique_lock<std::mutex> ul(mtx_);
        count_++;
        while (count_ < max_count_)
        {
            cv_.wait(ul);
        }
        cv_.notify_all();
    }

private:
    uint count_ = 0;
    const uint max_count_;
    std::mutex mtx_;
    std::condition_variable cv_;
};

constexpr uint num_threads = 10;
Barrier barrier(num_threads);
uint tracker = 0;
std::mutex mtx_;

void IncrementByThree() {
    std::unique_lock<std::mutex> ul(mtx_);
    tracker += 3u;
    ul.unlock();
    barrier.wait();
}

void DoubleTheValue() {
    barrier.wait();
    std::unique_lock<std::mutex> ul(mtx_);
    tracker *= 2;
}

int main() {
    std::vector<std::thread> thread_vec;

    for (int i = 0; i < 5; i++) {
        std::thread th(DoubleTheValue);
        thread_vec.push_back(std::move(th));
    }

    for (int i = 0; i < 5; i++) {
        std::thread th(IncrementByThree);
        thread_vec.push_back(std::move(th));
    }

    for (auto & th: thread_vec) {
        th.join();
    }

    printf("tracker = %d\n", tracker);

    return 0;
}