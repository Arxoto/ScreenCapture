#include "Timeout.h"
#include <future>
#include <thread>

Timeout::Timeout(std::function<void()> callBack):callBack{callBack}
{
    startTime = std::chrono::steady_clock::now() + std::chrono::years(1);
    t = std::thread(&Timeout::asyncTask, this);
}

Timeout::~Timeout()
{
    // ֪ͨ�첽������ֹ
    shouldTerminate = true;

    // �ȴ��첽�������
    if (t.joinable()) {
        t.join();
    }
}

void Timeout::Start()
{
    startTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(800);
}

void Timeout::asyncTask() {
    while (!shouldTerminate) {
        auto now = std::chrono::steady_clock::now();
        if (now>startTime) {
            callBack();
            startTime = std::chrono::steady_clock::now() + std::chrono::years(1);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
