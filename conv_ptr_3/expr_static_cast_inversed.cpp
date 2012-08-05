// [conv.ptr]/3
// A prvalue of type "pointer to cv D", where D is a class type, can be
// converted to a prvalue of type "pointer to cv B", where B is a base class
// (Clause 10) of D. If B is an inaccessible (Clause 11) or ambiguous (10.2)
// base class of D, a program that necessitates this conversion is
// ill-formed. ...
//
// [expr.static.cast]/7
// The inverse of any standard conversion sequence (Clause 4) not containing
// an lvalue-to-rvalue (4.1), array-to-pointer (4.2), function-to-pointer
// (4.3), null pointer (4.10), null member pointer (4.11), or boolean (4.12)
// conversion, can be performed explicitly using static_cast. A program is
// ill-formed if it uses static_cast to perform the inverse of an ill-formed
// standard conversion sequence. [ Example:
//   struct B { };
//   struct D : private B { };
//   void f() {
//     static_cast<D*>((B*)0);             // Error: B is a private base of D.
//     static_cast<int B::*>((int D::*)0); // Error: B is a private base of D.
//   }
// -end example ]

struct B
{};

struct D
  : private B
{};

template<typename T>
T &&declval();

template<typename T, typename = decltype(static_cast<D *>(declval<T *>()))>
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
  static_assert(!test<B>(0), "");
  static_assert(test<D>(0), "");
}
