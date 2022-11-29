#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <iterator>

struct Person {
    std::string first_name;
    std::string second_name;
};

namespace rng = std::ranges;
namespace view = rng::views;

void first_task() {
    auto square = [](int i) { return i * i; };
    auto not_divisible = [](int i) { return i % 5 != 0; };
    auto to_string = [](int i) { return std::to_string(i); };
    auto out_numbers = view::iota(10, 100) | view::transform(square) | view::filter(not_divisible) | view::transform(to_string);
    for(auto element: out_numbers) {
        std::cout << element << " ";
    }
}

template <typename InputIter>
auto sum(InputIter begin, InputIter end) {
    auto sum{ *begin };
    for (auto iter{ ++begin }; iter != end; ++iter) {
        sum += *iter;
    }

    return sum;
}

void second_task() {
    std::vector<std::pair<Person, unsigned int>> people = {
        {{"Ivan", "Ivanov"}, 11},
        {{"Petr", "Petrov"}, 66},
        {{"Sidor", "Sidorov"}, 34},
        {{"Ilya", "Ilyin"}, 23},
        {{"Artem", "Artemov"}, 47}
    };
    std::vector<unsigned int> ages;

    auto age_filter = [](std::pair<Person, unsigned int> pair) { return pair.second >= 12 && pair.second <= 65; };
    auto mapping = [](std::pair<Person, unsigned int> pair) { return pair.second; };

    auto preprocessing = people | view::filter(age_filter) | view::transform(mapping);
    // int count = rng::count(preprocessing);
    int age_sum = sum(preprocessing.begin(), preprocessing.end());
    int count = std::count_if(preprocessing.begin(), preprocessing.end(), [](auto) { return true; });
    std::cout << static_cast<double>(age_sum) / count;
}

template <typename InputIter, typename OutputIter>
void myCopy(InputIter begin , InputIter end , OutputIter target) {
    for (auto iter { begin }; iter != end; ++iter , ++ target) { *target = *iter; }
}

std::ostream& operator<<(std::ostream& stream, const Person& person) {
    stream << person.first_name << " " << person.second_name;
    return stream;
}

void third_task() {
    std::vector<std::pair<Person, unsigned int>> people = {
        {{"Ivan", "Ivanov"}, 11},
        {{"Petr", "Petrov"}, 66},
        {{"Sidor", "Sidorov"}, 34},
        {{"Ilya", "Ilyin"}, 23},
        {{"Artem", "Artemov"}, 47}
    };

    auto get_person_name = [](auto pair) { return pair.first; };

    auto first_four = people | view::take(4) | view::transform(get_person_name);
    myCopy(first_four.begin(), first_four.end(), std::ostream_iterator<Person>(std::cout, "\n"));

    auto second_names = first_four | view::transform([](auto person){ return person.second_name; });
    myCopy(second_names.begin(), second_names.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

void fourth_task() {
    std::vector<int> for_numbers;
    auto numbers_stream = rng::istream_view<int>(std::cin) | view::take_while([](int x) { return x != -1; });
    for (const auto& number: numbers_stream) {
        for_numbers.push_back(number);
    }
    myCopy(for_numbers.begin(), for_numbers.end(), std::ostream_iterator<int>(std::cout, " "));

    std::vector<int> numbers;

    rng::copy(numbers_stream.begin(), numbers_stream.end(), std::back_inserter(numbers));

    myCopy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
}

template <typename T> concept Number = std::is_integral<T>::value || std::is_floating_point<T>::value;
template <typename T> concept StringConvertible = requires(T t) { std::to_string(t); };

template <typename T, typename U>
requires Number<T> && Number<U> && StringConvertible<T> && StringConvertible<U>
std::string concat(T t, U u) {
    return std::to_string(t) + std::to_string(u);
}

void fifth_task() {
    std::cout << concat(1, 2.4) << std::endl;
    std::cout << concat(2, 3) << std::endl;
}

int main() {
    fifth_task();
}