// [conv.ptr]/3
// A prvalue of type "pointer to cv D", where D is a class type, can be
// converted to a prvalue of type "pointer to cv B", where B is a base class
// (Clause 10) of D. If B is an inaccessible (Clause 11) or ambiguous (10.2)
// base class of D, a program that necessitates this conversion is
// ill-formed. ...
//
// [expr.rel]/2
// The usual arithmetic conversions are performed on operands of arithmetic
// or enumeration type. Pointer conversions (4.10) and qualification
// conversions (4.4) are performed on pointer operands (or on a pointer
// operand and a null pointer constant, or on two null pointer constants, at
// least one of which is non-integral) to bring them to their composite
// pointer type. If one operand is a null pointer constant, the composite
// pointer type is std::nullptr_t if the other operand is also a null pointer
// constant or, if the other operand is a pointer, the type of the other
// operand. Otherwise, if one of the operands has type "pointer to cv1 void,"
// then the other has type "pointer to cv2 T" and the composite pointer type
// is "pointer to cv12 void," where cv12 is the union of cv1 and cv2.
// Otherwise, the composite pointer type is a pointer type similar (4.4) to
// the type of one of the operands, with a cv-qualification signature (4.4)
// that is the union of the cv-qualification signatures of the operand types.
// ...

struct B
{};

struct D
  : private B
{};

template<typename T>
T &&declval();

template<typename T, typename = decltype(declval<B *>() < declval<T *>())>
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
