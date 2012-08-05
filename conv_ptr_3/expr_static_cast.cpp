// [conv.ptr]/3
// A prvalue of type "pointer to cv D", where D is a class type, can be
// converted to a prvalue of type "pointer to cv B", where B is a base class
// (Clause 10) of D. If B is an inaccessible (Clause 11) or ambiguous (10.2)
// base class of D, a program that necessitates this conversion is
// ill-formed. ...
//
// [expr.static.cast]/4
// Otherwise, an expression e can be explicitly converted to a type T using a
// static_cast of the form static_-cast<T>(e) if the declaration T t(e); is
// well-formed, for some invented temporary variable t (8.5). The effect of
// such an explicit conversion is the same as performing the declaration and
// initialization and then using the temporary variable as the result of the
// conversion. The expression e is used as a glvalue if and only if the
// initialization uses it as a glvalue.

struct B
{};

struct D
  : private B
{};

template<typename T>
T &&declval();

template<typename T, typename = decltype(static_cast<B *>(declval<T *>()))>
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
