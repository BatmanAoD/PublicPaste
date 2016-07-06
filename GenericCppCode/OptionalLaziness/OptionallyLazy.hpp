#pragma once

#include <type_traits>
#include <utility>

// Uses dynamic dispatch to permit lazy OR eager argument evaluation at the
// caller's discretion, with uniform access to the final value from the callee's
// perspective.
template <typename VAL_TYPE>
class LazyType_Base
{
  protected:
    // For LazyType_TrueLazy
    template <typename CALLABLE>
    LazyType_Base(CALLABLE&& expr)
    { 
      static_assert(
          std::is_same<
              typename std::remove_reference<decltype(expr())>::type, VAL_TYPE
            >::value,
          "Expression does not evaluate to correct type!");
    }
    // For LazyType_Eager
    // =default is not permitted by GCC here; see
    // http://stackoverflow.com/q/38213809/1858225
    LazyType_Base(void) {}
    
    // C++14: move-constructor must be defined for use by MakeLazy()
    LazyType_Base(LazyType_Base&&) =default;
    
  public:
    virtual ~LazyType_Base(void) =default;
    
    virtual operator VAL_TYPE(void) =0;
};

// Takes an arbitrary expression and creates a class that will evaluate the
// expression when necessary.
template <typename VAL_TYPE, typename CALLABLE>
class LazyType_TrueLazy : public LazyType_Base<VAL_TYPE>
{
  // It's not clear how to declare a `friend` function correctly here.
  // friend LazyType_TrueLazy<VAL_TYPE, CALLABLE> MakeLazy<CALLABLE>(CALLABLE&& expr);
  // With a working friend declaration, make all constructors private; `protect`
  // default constructors in `LazyType_Base`
  
  public:
    LazyType_TrueLazy(CALLABLE&& expr)
      : LazyType_Base<VAL_TYPE>{std::forward<CALLABLE>(expr)}
      , expr_{std::forward<CALLABLE>(expr)}
    {}
    
    operator VAL_TYPE(void) override final
    {
      return expr_();
    }

  private:
    CALLABLE expr_;
};

// If VAL_TYPE is the same as EXPR_TYPE, then we do not have a truly lazy
// instantiation.
template <typename VAL_TYPE>
class LazyType_Eager : public LazyType_Base<VAL_TYPE>
{
  public:
    LazyType_Eager(
        VAL_TYPE&& final_val)
      : LazyType_Base<VAL_TYPE>{}
      , val_{final_val}
    {}

    operator VAL_TYPE(void) override final
    {
      return val_;
    }
  
  private:
    VAL_TYPE val_;
};

// C++14: since template `auto` arguments are not permitted prior to C++17,
// we need a helper function to evaluate the type of the callable, in case it's
// a lambda.
template <typename CALLABLE>
auto MakeLazy(CALLABLE&& expr)
{
  return LazyType_TrueLazy<
            typename std::remove_reference<decltype(expr())>::type, CALLABLE>{
      std::forward<CALLABLE>(expr)};
}

#define LAZY_ARG(expr) \
  MakeLazy([&](void)->auto { return expr; })

// Is there some way to create an implicit conversion to `LazyType_Eager` for
// all types that will be applied for any attempted conversion to
// `LazyType_Base`?
#define EAGER_ARG(val) \
  LazyType_Eager<typename std::remove_reference<decltype(val)>::type>{val}

// Must provide a REFERENCE so that the actual type will not be sliced...but we
// don't actually want a mutable reference to a long-lived object, so we take an
// r-value reference. This is very simple to use with the `LAZY_ARG` and
// `EAGER_ARG` macros.
// XXX This apparently DOES NOT work with `const` types.
#define OPTIONALLY_LAZY(type) \
  LazyType_Base<type>&&
