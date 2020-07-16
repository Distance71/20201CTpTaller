#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class Semaphore
{
public:
    explicit Semaphore() : m_count(0) {}
    Semaphore(const Semaphore&&) = delete;
    Semaphore(Semaphore&&) = delete;
    Semaphore& operator = (const Semaphore&) = delete;
    Semaphore& operator = (Semaphore&&) = delete;
    ~Semaphore() = default;

    void post()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        ++m_count;
        m_cv.notify_one();
    }

    void wait()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [&]{ return m_count > 0; });
        --m_count;
    }

private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    int m_count;
};

#endif
