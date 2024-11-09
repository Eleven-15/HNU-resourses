// thread_pool.h

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <functional>
#include <queue>
#include <thread>
#include <vector>

// 线程池类
class ThreadPool
{
public:
    explicit ThreadPool(size_t numThreads) : stop(false)
    {
        for (size_t i = 0; i < numThreads; ++i)
        {
            threads.emplace_back([this]
                                 {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this] { return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) {
                            return;
                        }
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                } });
        }
    }

    // 添加任务到线程池
    template <class F, class... Args>
    void enqueue(F &&f, Args &&...args)
    {
        auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.emplace(task);
        }
        condition.notify_one();
    }

    // 关闭线程池
    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : threads)
        {
            worker.join();
        }
    }

private:
    std::vector<std::thread> threads;        // 线程池中的线程
    std::queue<std::function<void()>> tasks; // 任务队列
    std::mutex queueMutex;                   // 任务队列互斥锁
    std::condition_variable condition;       // 条件变量
    bool stop;                               // 是否停止
};

#endif // THREAD_POOL_H
