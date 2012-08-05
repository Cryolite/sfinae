// [conv.ptr]/3
// A prvalue of type "pointer to cv D", where D is a class type, can be
// converted to a prvalue of type "pointer to cv B", where B is a base class
// (Clause 10) of D. If B is an inaccessible (Clause 11) or ambiguous (10.2)
// base class of D, a program that necessitates this conversion is
// ill-formed. ...
//
// [expr.new]/15
// A new-expression that creates an object of type T initializes that object
// as follows:
//   - If the new-initializer is omitted, the object is default-initialized
//     (8.5); if no initialization is performed, the object has indeterminate
//     value.
//   - Otherwise, the new-initializer is interpreted according to the
//     initialization rules of 8.5 for directinitialization.

struct B
{};

struct D
  : private B
{};

template<typename T>
T &&declval();

template<typename T, typename = decltype(new B *(declval<T *>()))>
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
