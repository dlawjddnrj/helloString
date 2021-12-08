#ifndef THREADEXCLASS_H
#define THREADEXCLASS_H
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>

class ThreadExClass {

public:
    ThreadExClass() : data(10000), saveNumber(4) { };
    ~ThreadExClass(){ };

    void threadNumber() {
        for (int i = 0; i < 10000; i++) {
            data[i] = i;
        }

        for(int i = 0; i < 4; i++) {
            numberWorkers.push_back(std::thread(worker, data.begin() + i * 2500,
                             data.begin() + (i + 1) * 2500, &saveNumber[i]));
        }

        for(int i = 0; i < 4; i++) {
            numberWorkers[i].join();
        }

        for (int i = 0; i < 4; i++) {
            total += saveNumber[i];
        }

        std::cout << "전체 합 : " << total << std::endl;
    }

    static void worker(std::vector<int>::iterator start, std::vector<int>::iterator end,
                int* result) {
      int sum = 0;
      for (auto itr = start; itr < end; ++itr) {
        sum += *itr;
      }
      *result = sum;

      // 쓰레드의 id 를 구한다.
//      std::thread::id this_id = std::this_thread::get_id();
      std::stringstream ss;
      ss << std::this_thread::get_id();
      uint64_t id = std::stoull(ss.str());
      printf("쓰레드 %ld 에서 %d 부터 %d 까지 계산한 결과 : %d \n", id, *start,
             *(end - 1), sum);
    }

    void threadCounter() {
        for (int i = 0; i < 4; i++) {
            countWorkers.push_back(std::thread(counterFunc, std::ref(counter), std::ref(mMutex)));
        }

        for (int i = 0; i < 4; i++) {
            countWorkers[i].join();
        }

        std::cout << "Counter 최종 값 : " << counter << std::endl;
    }

    static void counterFunc(int& count, std::mutex& m) {
        for (int i = 0; i < 10000; i++) {
            std::lock_guard<std::mutex> lock(m);
            count += 1;
//            m.lock();
//            count += 1;
//            m.unlock();
        // scope 를 빠져 나가면 lock 이 소멸되면서
        // m 을 알아서 unlock 한다.
        }
    }

private:
    std::vector<int> data;
    std::vector<int> saveNumber;
    std::vector<std::thread> numberWorkers;
    std::vector<std::thread> countWorkers;
    int total = 0;
    int counter = 0;
    std::mutex mMutex;
};

class ThreadTimeEx {
public:
    ThreadTimeEx() {
        condition.store(true);
    }
    ~ThreadTimeEx() {
        condition.store(false);
        if(mThread.joinable())
        {
            mThread.join();
        }
        if(mThread2.joinable())
        {
            mThread2.join();
        }
        if(mThread3.joinable())
        {
            mThread3.join();
        }
    }

    void run() {
        mThread = std::thread(std::bind(&ThreadTimeEx::countTime, this));
        mThread2 = std::thread(std::bind(&ThreadTimeEx::countTimeTwo, this, "JungWoo"));
    }

    void tempRun() {
        mThread3 = std::thread(std::bind(&ThreadTimeEx::countTimeThree, this));
    }

    void countTime() {
        int timeCounter = 1;
        while (condition) {
            std::cout << "time : " << timeCounter++ << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void countTimeTwo(std::string s) {
        while (condition) {
            std::cout << "str : " << "Lim " + s << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void countTimeThree() {
        while (condition) {
            std::cout << "Three Function..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

private:
    std::thread mThread;
    std::thread mThread2;
    std::thread mThread3;
    std::atomic_bool condition;
};

#endif // THREADEXCLASS_H
