// [conv.ptr]/3
// A prvalue of type "pointer to cv D", where D is a class type, can be
// converted to a prvalue of type "pointer to cv B", where B is a base class
// (Clause 10) of D. If B is an inaccessible (Clause 11) or ambiguous (10.2)
// base class of D, a program that necessitates this conversion is
// ill-formed. ...
//
// [expr.type.conv]/3
// Similarly, a simple-type-specifier or typename-specifier followed by a
// braced-init-list creates a temporary object of the specified type
// direct-list-initialized (8.5.4) with the specified braced-init-list, and
// its value is that temporary object as a prvalue.
//
// [dcl.init.list]/3
// List-initialization of an object or reference of type T is defined as
// follows:
//   - ...
//   - ...
//   - ...
//   - ...
//   - Otherwise, if the initializer list has a single element of type E and
//     either T is not a reference type or its referenced type is
//     reference-related to E, the object or reference is initialized from
//     that element; if a narrowing conversion (see below) is required to
//     convert the element to T, the program is ill-formed. ...
//   ...

struct B
{};

struct D
  : private B
{};

template<typename T>
T &&declval();

typedef B *PB;

template<typename T, typename = decltype(PB{ declval<T *>() })>
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
