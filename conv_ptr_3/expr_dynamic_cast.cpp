// [conv.ptr]/3
// A prvalue of type "pointer to cv D", where D is a class type, can be
// converted to a prvalue of type "pointer to cv B", where B is a base class
// (Clause 10) of D. If B is an inaccessible (Clause 11) or ambiguous (10.2)
// base class of D, a program that necessitates this conversion is
// ill-formed. ...
//
// [expr.dynamic.cast]/5
// If T is "pointer to cv1 B" and v has type "pointer to cv2 D" such that B
// is a base class of D, the result is a pointer to the unique B subobject of
// the D object pointed to by v. Similarly, if T is "reference to cv1 B" a v
// has type cv2 D such that B is a base class of D, the result is the unique
// B subobject of the D object referred to by v. The result is an lvalue if T
// is an lvalue reference, or an xvalue if T is an rvalue reference. In both
// the pointer and reference cases, the program is ill-formed if cv2 has
// greater cv-qualification than cv1 or if B is an inaccessible or ambiguous
// base class of D. ...

struct B
{};

struct D
  : private B
{};

template<typename T>
T &&declval();

template<typename T, typename = decltype(dynamic_cast<B *>(declval<T *>()))>
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
