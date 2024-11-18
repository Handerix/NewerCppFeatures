#include "InfiniteGenerator.hpp"
#include "FiniteGenerator.hpp"
#include "TemplateGeneratorWithIterators.hpp"
#include <iostream>
#include <functional>
#include <optional>


InfiniteGenerator genIota() // NOLINT(*-static-accessed-through-instance)
{
    for (int i = 0; true; i++)
    {
        co_yield i;
    }
}

void genIotaUsage()
{
    auto gen = genIota();

    for (int i = 0; i < 5; i++)
    {
        std::cout << gen() << " ";
    }
    std::cout << std::endl;
}

FiniteGenerator genThirdWheel() // NOLINT(*-static-accessed-through-instance)
{
    for (auto el: {1, 7, 11, 13, 17, 19, 23, 29})
    {
        co_yield el;
    }
}

void genThirdWheelUsage()
{
    auto gen = genThirdWheel();

    while (gen.advance())
    {
        std::cout << gen.getValue() << " ";
    }
    std::cout << std::endl;
}


template <typename Ret>
TemplateGeneratorWithIterators<Ret> genFromFunction(
    std::function<std::optional<Ret>()> func,
    std::function<bool()> additionalShouldContinue = []{ return true; })
{
    while (additionalShouldContinue())
    {
        auto result = func();
        if (!result)
        {
            break;
        }
        co_yield *result;
    }
}

void genFromFunctionUsage()
{
    auto gen = genFromFunction([a = 1]()
        {
            for ()
            {

            }
            std::optional(1);
        });
}


int main()
{
    std::cout << "genIotaUsage():" << std::endl;
    genIotaUsage();

    std::cout << "genThirdWheelUsage():" << std::endl;
    genThirdWheelUsage();

    return 0;
}
