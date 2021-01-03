#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

class Semaphore {
public:
    Semaphore(uint count, uint max_count) 
        : count_(count), max_count_(max_count) {}

    void acquire() {
        std::unique_lock<std::mutex> ul(mtx_);
        while (count_ == 0) {
            cv_.wait(ul);
        }
        count_--;
        if (count_ == max_count_ - 1) cv_.notify_all();
    }

    void release() {
        std::unique_lock<std::mutex> ul(mtx_);
        while (count_ == max_count_) {
            cv_.wait(ul);
        }
        count_++;
        if (count_ == 1) cv_.notify_all();
    }

private:
    uint count_ = 0, max_count_ = 0;
    std::mutex mtx_;
    std::condition_variable cv_;
};

uint num_elements = 5;
uint num_free_slots = num_elements;
Semaphore semaphore(num_free_slots, num_elements);

void User(int index) {
    semaphore.acquire();
    printf("User %d acquired semaphore\n", index);
    std::this_thread::sleep_for(std::chrono::milliseconds(index * 500));
    printf("User %d released semaphore\n", index);
    semaphore.release();
}

int main() {
    const int num_users = 10;
    std::vector<std::thread> user_vec;
    for (int i = 0; i < num_users; i++) {
        std::thread th(User, i);
        user_vec.push_back(std::move(th));
    }

    for (auto & th : user_vec) {
        th.join();
    }
    return 0;
}