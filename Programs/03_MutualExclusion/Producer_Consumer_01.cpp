// ===========================================================================
// Producer Consumer Problem
// ===========================================================================

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <chrono>
#include <thread>

#include "../Logger/Logger.h"

namespace ConsumerProducerOne
{
    class ConsumerProducer {

    private:
        std::queue<int> m_data;
        std::mutex m_mutex;

        void produce() {
            int nextNumber = 0;
            while (true) {

                // sleep some seconds
                std::this_thread::sleep_for(std::chrono::seconds(1));

                nextNumber++;

                // RAII idiom
                Logger::log(std::cout, "> Producer");
                {
                    std::scoped_lock<std::mutex> lock (m_mutex);
                    m_data.push(nextNumber);
                }

                Logger::log(std::cout, "Added ", nextNumber, " to queue.");
            }
        }

        void consume() {
            int number;
            while (true) {

                number = 0;

                // RAII idiom
                Logger::log(std::cout, "> Consumer");
                {
                    std::scoped_lock<std::mutex> lock (m_mutex);
                    if (!m_data.empty()) {
                        number = m_data.front();
                        m_data.pop();
                    }
                }

                if (number > 0) {
                    Logger::log(std::cout, "Popped ", number, '.');
                }
                else {
                    Logger::log(std::cout, "Stack empty.");
                }
            }
        }

    public:
        void run() {
            std::thread t1(&ConsumerProducer::produce, this);
            std::thread t2(&ConsumerProducer::consume, this);
            t1.join();
            t2.join();
        }
    };

    void test() {
        ConsumerProducer cp;
        cp.run();
    }
}

void test_mutual_exclusion_01() {
    using namespace ConsumerProducerOne;
    test();
}

// ===========================================================================
// End-of-File
// ===========================================================================
