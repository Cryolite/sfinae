// [conv.ptr]/3
// A prvalue of type "pointer to cv D", where D is a class type, can be
// converted to a prvalue of type "pointer to cv B", where B is a base class
// (Clause 10) of D. If B is an inaccessible (Clause 11) or ambiguous (10.2)
// base class of D, a program that necessitates this conversion is
// ill-formed. ...
//
// [expr.cond]/3
// Otherwise, if the second and third operand have different types and either
// has (possibly cv-qualified) class type, or if both are glvalues of the
// same value category and the same type except for cv-qualification, an
// attempt is made to convert each of those operands to the type of the
// other. The process for determining whether an operand expression E1 of
// type T1 can be converted to match an operand expression E2 of type T2 is
// defined as follows:
//   - ...
//   - ...
//   - If E2 is an rvalue or if neither of the conversions above can be done
//     and at least one of the operands has (possibly cv-qualified) class
//     type:
//       - ...
//       - Otherwise (i.e., if E1 or E2 has a nonclass type, or if they both
//         have class types but the underlying classes are not either the
//         same or one a base class of the other): E1 can be converted to
//         match E2 if E1 can be implicitly converted to the type that
//         expression E2 would have if E2 were converted to a prvalue (or
//         the type it has, if E2 is a prvalue).
//     Using this process, it is determined whether the second operand can be
//     converted to match the third operand, and whether the third operand
//     can be converted to match the second operand. If both can be
//     converted, or one can be converted but the conversion is ambiguous,
//     the program is ill-formed. If neither can be converted, the operands
//     are left unchanged and further checking is performed as described
//     below. If exactly one conversion is possible, that conversion is
//     applied to the chosen operand and the converted operand is used in
//     place of the original operand for the remainder of this section.

struct B
{};

struct D
  : private B
{};

template<typename T>
T &&declval();

template<typename T, typename = decltype(false ? declval<B *>() : declval<T *>())>
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
