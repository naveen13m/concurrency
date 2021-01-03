#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

struct data {
    int value{0};
    bool status{false};
};

std::mutex mtx_;
std::condition_variable cv_;
data data_;

void generate_data() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::unique_lock<std::mutex> ul(mtx_);
    data_.value = 10;
    data_.status = true;
    ul.unlock();
    cv_.notify_one();
}

void process_data() {
    int result;

    std::unique_lock<std::mutex> ul(mtx_);
    cv_.wait(ul, [](){return data_.status == true;});
    result = 3 * data_.value;
    ul.unlock();
    printf("Result is: %d\n", result);
}

int main() {
    std::thread generator(generate_data);
    std::thread processor(process_data);

    generator.join();
    processor.join();
    return 0;
}