#pragma once

#include <coroutine>
#include <exception>


struct InfiniteGenerator
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

        InfiniteGenerator get_return_object()
        {
            return {handle_type::from_promise(*this)};
        }

        static void unhandled_exception()
        {
            std::rethrow_exception(std::current_exception());
        }

        int _result {};
    };

    using handle_type = std::coroutine_handle<promise_type>;

    InfiniteGenerator(handle_type handler) // NOLINT(*-explicit-constructor)
            : _handler(handler)
    {}

    ~InfiniteGenerator()
    {
        _handler.destroy();
    }

    int operator()() const
    {
        _handler();
        return _handler.promise()._result;
    }

    handle_type _handler;
};
