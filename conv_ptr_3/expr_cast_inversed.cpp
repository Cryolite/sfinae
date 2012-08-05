// [conv.ptr]/3
// A prvalue of type "pointer to cv D", where D is a class type, can be
// converted to a prvalue of type "pointer to cv B", where B is a base class
// (Clause 10) of D. If B is an inaccessible (Clause 11) or ambiguous (10.2)
// base class of D, a program that necessitates this conversion is
// ill-formed. ...
//
// [expr.cast]/4
// The conversions performed by
//   - a const_cast (5.2.11),
//   - a static_cast (5.2.9),
//   - a static_cast followed by a const_cast,
//   - a reinterpret_cast (5.2.10), or
//   - a reinterpret_cast followed by a const_cast,
// can be performed using the cast notation of explicit type conversion. The
// same semantic restrictions and behaviors apply, with the exception that in
// performing a static_cast in the following situations the conversion is
// valid even if the base class is inaccessible:
//   - a pointer to an object of derived class type or an lvalue or rvalue of
//     derived class type may be explicitly converted to a pointer or
//     reference to an unambiguous base class type, respectively;
//   - a pointer to member of derived class type may be explicitly converted
//     to a pointer to member of an unambiguous non-virtual base class type;
//   - a pointer to an object of an unambiguous non-virtual base class type,
//     a glvalue of an unambiguous non-virtual base class type, or a pointer
//     to member of an unambiguous non-virtual base class type may be
//     explicitly converted to a pointer, a reference, or a pointer to member
//     of a derived class type, respectively.
// ...

struct B
{};

struct D
  : private B
{};

template<typename T>
T &&declval();

template<typename T, typename = decltype((D *)declval<T *>())>
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
  static_assert(test<D>(0), "");
}
