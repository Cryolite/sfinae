// [conv.ptr]/3
// A prvalue of type "pointer to cv D", where D is a class type, can be
// converted to a prvalue of type "pointer to cv B", where B is a base class
// (Clause 10) of D. If B is an inaccessible (Clause 11) or ambiguous (10.2)
// base class of D, a program that necessitates this conversion is
// ill-formed. ...
//
// [expr.call]/4
// When a function is called, each parameter (8.3.5) shall be initialized
// (8.5, 12.8, 12.1) with its corresponding argument. ...
//
// [dcl.init]/16
// The semantics of initializers are as follows. The destination type is the
// type of the object or reference being initialized and the source type is
// the type of the initializer expression. If the initializer is not a single
// (possibly parenthesized) expression, the source type is not defined.
//   - ...
//   - ...
//   - ...
//   - ...
//   - ...
//   - ...
//   - ...
//   - Otherwise, the initial value of the object being initialized is the
//     (possibly converted) value of the initializer expression. Standard
//     conversions (Clause 4) will be used, if necessary, to convert the
//     initializer expression to the cv-unqualified version of the
//     destination type; no user-defined conversions are considered. If the
//     conversion cannot be done, the initialization is ill-formed. ...

struct B
{};

struct D
  : private B
{};

template<typename T>
T &&declval();

void f(B *);

template<typename T, typename = decltype(f(declval<T *>()))>
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
