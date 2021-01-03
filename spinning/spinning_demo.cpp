#include <thread>
#include <mutex>
#include <chrono>

struct data {
    int value{0};
    bool status{false};
};

std::mutex mtx_;
data data_;

void generate_data() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::unique_lock<std::mutex> ul(mtx_);
    data_.value = 10;
    data_.status = true;
    ul.unlock();
}

void process_data() {
    int result;

    std::unique_lock<std::mutex> ul(mtx_);
    while (true) {
        if (data_.status == true) {
            result = 3 * data_.value;
            break;
        } else {
            ul.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            ul.lock();
        }
    }
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