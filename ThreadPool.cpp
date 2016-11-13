#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool(size_t p_size) : size(p_size)
{

}

ThreadPool::~ThreadPool()
{
    //stop();
}

void ThreadPool::start()
{
    if (!threads.empty())
    {
      throw std::runtime_error("ThreadPool started already");
    }

    std::string threadCreationError;
    for (size_t i = 0; (i < size) && threadCreationError.empty(); ++i)
    {
      try
      {
        auto funcCallable = std::bind(&ThreadPool::threadFunc, this);
        ThreadPtr newThread = std::make_shared<std::thread>(std::thread(funcCallable));
        threads.push_back(newThread);
      }
      catch (const std::exception e)
      {
        threadCreationError = e.what();
        break;
      }
    }

    if (!threadCreationError.empty())
    {
      std::cout << "ThreadPool thread creation error: " << threadCreationError << ", ThreadPool not started at all" << std::endl;
      throw std::runtime_error(threadCreationError);
    }
}

void ThreadPool::stop()
{
    int i = 0;
    for (auto job : threads)
    {
      (*job).join();
        i++;
      std::cout << "join "<< i << std::endl;
    }

    threads.clear();
}

void ThreadPool::add(const Task & task, const PixelXY &pixel)
{
    queue.push(task, pixel);
}

void ThreadPool::threadFunc()
{
    while (!queue.empty())
    {
      std::pair<Task, PixelXY> exec = queue.waitForJob(); //popraw TODO
      exec.first(exec.second);
    }
}
