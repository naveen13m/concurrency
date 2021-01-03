#include <thread>
#include <chrono>

void thread_job() {
    printf("Hello from thread_job() running on thread %x.\n", 
        std::this_thread::get_id());
    printf("Start of 3 sec wait in thread_job().\n");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    printf("End of 3 sec wait in thread_job().\n");
}

int main() {
    printf("Hello from main() running on thread %x.\n", 
        std::this_thread::get_id());
    std::thread T1(thread_job);

    printf("Waiting for T1 to complete its job.\n");
    T1.join();
    printf("Job done.\n");

    return 0;
}