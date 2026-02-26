#include <gtest/gtest.h>
#include "./spsc_queue.h"


TEST(QUEUE, seq)
{
    constexpr int iterations = 6;

    Queue<int> queue(10);
    auto func_push = [&queue](){
        int i = 0;
        while(i < iterations)
        {
            queue.push(1);
            i++;
        }
    };
    int result = 0;
    std::thread t1(func_push);
    t1.join();
    int p = 0;
    while (queue.pop(p))
    {
        result += p;
    }
    EXPECT_EQ(iterations, result);
}

TEST(QUEUE, concurrent)
{
    constexpr int iterations_push = 1000000;
    constexpr int iterations_pop = 900000;

    Queue<int> queue(1024);
    auto func_push = [&queue](){
        int i = 0;
        while(i < iterations_push)
        {
            queue.push(1);
            i++;
        }
    };

    auto func_pop = [&queue](){
        int i = 0;
        while(i < iterations_pop)
        {
            int a{};
            queue.pop(a);
            i++;
        }
    };
    int result = 0;
    std::thread t1(func_push);
    std::thread t2(func_pop);
    t1.join();
    t2.join();
    EXPECT_EQ(queue.size(), iterations_push - iterations_pop);
}
