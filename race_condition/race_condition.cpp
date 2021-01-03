#include <thread>

uint counter = 0;

void increment_counter() {
    counter++;
}

void double_counter() {
    counter *= 2;
}

int main() {
    std::thread T1(increment_counter);
    std::thread T2(double_counter);

    T1.join();
    T2.join();

    printf("Expected = %d, Actual = %d, Error = %d\n", 
        2, counter, 2 - counter);

    return 0;
}