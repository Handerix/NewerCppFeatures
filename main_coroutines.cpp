#include <iostream>
#include <coroutine>


//class CoroTask;
//
//CoroTask coro(int max)
//{
//    std::cout << "coro " << max << " start\n";
//    for  (int val = 0; val < max; val++)
//    {
//        std::cout << "coro " << val << '/' << max << '\n';
//
//        co_await std::suspend_always();
//    }
//
//    std::cout << "coro " << max << " end\n";
//}


struct Generator
{
    struct promise_type
    {
        static std::suspend_always initial_suspend() noexcept
        {
            return {};
        }

        std::suspend_always yield_value(int value)
        {
            _result = value;
            return {};
        }

        static std::suspend_always final_suspend() noexcept
        {
            return {};
        };

        Generator get_return_object()
        {
            return {handle_type::from_promise(*this)};
        }

        static void unhandled_exception()
        {
            std::rethrow_exception(std::current_exception());
        }

        int _result;
    };

    using handle_type = std::coroutine_handle<promise_type>;

    Generator(handle_type handler)
    : _handler(handler)
    {}

    ~Generator()
    {
        _handler.destroy();
    }

    int operator()()
    {
        _handler();
        return _handler.promise()._result;
    }

    handle_type _handler;
};

Generator genIota()
{
    for (int i = 0; true; i++)
    {
        co_yield i;
    }
}


int main()
{
    auto gen = genIota();

    for (int i = 0; i < 5; i++)
    {
        std::cout << gen() << " ";
    }

//    auto coroTask = coro(3);
//
//    std::cout << "coro() started\n";
//
//    while (coroTask.resume())
//    {
//        std::cout << "coro() suspended";
//    }
//
//    std::cout << "coro() done\n";

    return 0;
}

