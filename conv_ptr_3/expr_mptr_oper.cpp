struct B
{};

struct D
  : private B
{};

int B::*pm = 0;

template<typename T>
T &&declval();

template<typename T, typename = decltype(declval<T *>()->*pm)>
constexpr bool test(int)
{
  return true;
}

template<typename T>
constexpr bool test(...)
{
  return false;
}

int main()
{
  static_assert(test<B>(0), "");
  static_assert(!test<D>(0), "");
}
