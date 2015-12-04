#include <cassert>
#include <type_traits>

#define RAW_VAL(enum_val) \
  static_cast<RawType>(enum_val)

#define ENUM_VAL(raw_val) \
  static_cast<ENUM_TYPE>(raw_val)

template <typename ENUM_TYPE, ENUM_TYPE beginVal, ENUM_TYPE endVal>
class EnumIterator
{
  using RawType = std::underlying_type_t<ENUM_TYPE>;

  static_assert(
      RAW_VAL(beginVal) <= RAW_VAL(endVal),
      "Cannot create iterator where 'beginVal' comes after 'endVal'!");

  // XXX TODO there MAY be undefined behavior if 'endVal' is the maximum
  // positive value of the underlying type, because '::end()' will cause a
  // wrap-around, which is not defined for signed types.
  // However, it seems unlikely that this would cause issues.
  // Nevertheless, it would be best to add a compile-time assertion or something
  // to ensure valid behavior.

  public:
    EnumIterator(void) noexcept
      : iter_(RAW_VAL(beginVal))
    {}

    EnumIterator(const ENUM_TYPE& start) noexcept
      : iter_{RAW_VAL(start)}
    {
      bool valid {
        iter_ >= RAW_VAL(beginVal)
          // '*end()' is the last valid enum value for iteration
        && iter_ <= RAW_VAL(*end())
      };
      assert(valid);
      // In release mode:
      if (!valid) *this = end();
    }
  
  private:    // Used by 'begin()' and 'end()'
    EnumIterator(
        const RawType& raw_start) noexcept
      : iter_{raw_start}
    {}

  public:

    EnumIterator operator++()
    {
      if (*this != end())
      {
        // Skip invalid enum values for iter_.
        do ++iter_; while (!IsEnumValid(**this) && *this != end());
      }

      return *this;
    }

    ENUM_TYPE operator*()
    {
      return ENUM_VAL(iter_);
    }

    EnumIterator begin()
    {
      static const EnumIterator beginIter{RAW_VAL(beginVal)};
      return beginIter;
    }

    EnumIterator end() {
      static const EnumIterator endIter{RAW_VAL(endVal) +1};
      return endIter;
    }

    bool operator!=(
        const EnumIterator& rhs)
    {
      return iter_ != rhs.iter_;
    }

  private:
    RawType iter_;
};

#undef RAW_VAL
#undef ENUM_VAL

//////////////////////////////////////////////////////////////////////////////
// USE EXAMPLE
#include <iostream>
#include <string>

enum class MyEnum
{
  FOO = 0,
  BAR = 10,
  BAZ = 20
};

bool IsEnumValid(MyEnum value)
{
  switch(value)
  {
    case MyEnum::FOO:
    case MyEnum::BAR:
    case MyEnum::BAZ:
      return true;
    default:
      return false;
  }
}

int main()
{
  using Iter_MyEnum = EnumIterator<
    MyEnum,
    MyEnum::FOO,
    MyEnum::BAZ>;

  for (Iter_MyEnum iter;
      iter != iter.end();
      ++iter)
  {
    std::cout << std::to_string(static_cast<int>(*iter)) << std::endl;
  }
  for (auto item : Iter_MyEnum{})
  {
    std::cout << std::to_string(static_cast<int>(item)) << std::endl;
  }
}
