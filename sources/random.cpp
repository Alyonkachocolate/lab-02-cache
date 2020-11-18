// Copyright [2020] <Alyona Dorodnyaya>

#include <cstddef>
#include <set>

// void - так как храним только указатели
void const** random(size_t length) {
  void const** arr = new void const*[length];
  std::set<size_t> used_rand{0u};
  size_t random;
  srand(length - 1);  // границы рандома
  void const** current = arr;
  static auto seed = static_cast<unsigned int>(time(nullptr));;
  for (size_t i = 0; i < length - 16; i+=16) {
    random = rand_r(&seed) % length;
    while (used_rand.count(random) != 0)  // проверка на наличие
      random = (random + 1) % length;
    used_rand.insert(random);
    *current = &arr[random];
    current = static_cast<void const**>(arr + random);  // переход к элементу
  }

  *current = nullptr;
  return arr;
}
