#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <numeric>

template <typename type>
class ThreadSafeQueue {
public:
    void push(type data) {
        std::unique_lock<std::mutex> ul(mtx_);
        buffer_.push(data);
        ul.unlock();
        if (buffer_.size() == 1) cv_.notify_one();
    }

    type pop() {
        std::unique_lock<std::mutex> ul(mtx_);
        while (buffer_.empty()) {
            cv_.wait(ul);
        }
        type data = buffer_.front();
        buffer_.pop();
        ul.unlock();
        return data;
    }

private:
    std::queue<type> buffer_;
    std::mutex mtx_;
    std::condition_variable cv_;
};

ThreadSafeQueue<int> buffer_;

void producer(uint start, uint end, uint &num_produced) {
    for (uint index = start; index < end; index++) {
        buffer_.push(index);
        num_produced = index - start + 1;
    }
}

void consumer(uint &num_consumed) {
    num_consumed = 0;
    while (true)
    {
        int data = buffer_.pop();
        if (data == -1) {
            buffer_.push(data);
            return;
        } else {
            num_consumed++;
        }
    }
}

int main() {
    constexpr uint num_producers = 6, num_consumers = 9;
    std::vector<std::thread> producer_vec;
    std::vector<std::thread> consumer_vec;
    std::array<uint, num_producers> num_produced;
    std::array<uint, num_consumers> num_consumed;

    for (uint index = 0; index < num_producers; index++) {
        uint start = 50 * index;
        uint end = 50 * (index + 1);
        std::thread th(producer, start, end, std::ref(num_produced[index]));
        producer_vec.push_back(std::move(th));
    }

    for (uint index = 0; index < num_consumers; index++) {
        std::thread th(consumer, std::ref(num_consumed[index]));
        consumer_vec.push_back(std::move(th));
    }

    for (std::thread &th : producer_vec) {
        th.join();
    }
    // All threads are done producing. Adding an end condition to signal the consumers to stop.
    buffer_.push(-1);

    for (auto &th : consumer_vec) {
        th.join();
    }

    uint total_produced, total_consumed;
    total_produced = std::accumulate(num_produced.begin(), num_produced.end(), 0);
    total_consumed = std::accumulate(num_consumed.begin(), num_consumed.end(), 0);
    
    printf("total_produced = %d, total_consumed = %d\n", total_produced, total_consumed);
    return 0;
}