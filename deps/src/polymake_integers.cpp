#include "polymake_includes.h"

#include "polymake_tools.h"

#include "polymake_functions.h"

#include "polymake_integers.h"

pm::Integer new_integer_from_bigint(jl_value_t* integer)
{
    pm::Integer* p;
    p = reinterpret_cast<pm::Integer*>(integer);
    return *p;
}

void polymake_module_add_integer(jlcxx::Module& polymake)
{

    polymake
        .add_type<pm::Integer>("pm_Integer",
                               jlcxx::julia_type("Integer", "Base"))
        .constructor<int32_t>()
        .constructor<int64_t>()
        .method("==", [](pm::Integer& a, pm::Integer& b) { return a == b; })
        .method("==", [](pm::Integer& a,
                         int64_t b) { return a == static_cast<long>(b); })
        .method("==", [](pm::Integer& a, int32_t b) { return a == b; })
        .method("==",
                [](int64_t a, pm::Integer& b) {
                    return static_cast<long>(a) == b;
                })
        .method("==", [](int32_t a, pm::Integer& b) { return a == b; })
        .method("<", [](pm::Integer& a, pm::Integer& b) { return a < b; })
        .method("<", [](pm::Integer& a,
                        int64_t      b) { return a < static_cast<long>(b); })
        .method("<", [](pm::Integer& a, int32_t b) { return a < b; })
        .method("<", [](int64_t      a,
                        pm::Integer& b) { return static_cast<long>(a) < b; })
        .method("<", [](int32_t      a,
                        pm::Integer& b) { return static_cast<long>(a) < b; })
        .method("<=", [](pm::Integer& a, pm::Integer& b) { return a <= b; })
        .method("<=", [](pm::Integer& a,
                         int64_t b) { return a <= static_cast<long>(b); })
        .method("<=", [](pm::Integer& a, int32_t b) { return a <= b; })
        .method("<=",
                [](int64_t a, pm::Integer& b) {
                    return static_cast<long>(a) <= b;
                })
        .method("<=", [](int32_t a, pm::Integer& b) { return a <= b; })

        .method("show_small_obj",
                [](pm::Integer& i) {
                    return show_small_object<pm::Integer>(i, false);
                })
        // the symmetric definitions are on the julia side
        .method("+", [](pm::Integer& a, pm::Integer& b) { return a + b; })
        .method("+", [](pm::Integer& a,
                        int64_t      b) { return a + static_cast<long>(b); })
        .method("+", [](pm::Integer& a, int32_t b) { return a + b; })
        .method("+", [](int64_t      a,
                        pm::Integer& b) { return static_cast<long>(a) + b; })
        .method("+", [](int32_t a, pm::Integer& b) { return a + b; })

        .method("*", [](pm::Integer& a, pm::Integer& b) { return a * b; })
        .method("*", [](pm::Integer& a,
                        int64_t      b) { return a * static_cast<long>(b); })
        .method("*", [](pm::Integer& a, int32_t b) { return a * b; })
        .method("*", [](int64_t      a,
                        pm::Integer& b) { return static_cast<long>(a) * b; })
        .method("*", [](int32_t a, pm::Integer& b) { return a * b; })

        .method("-", [](pm::Integer& a, pm::Integer& b) { return a - b; })
        .method("-", [](pm::Integer& a,
                        int64_t      b) { return a - static_cast<long>(b); })
        .method("-", [](pm::Integer& a, int32_t b) { return a - b; })
        .method("-", [](int64_t      a,
                        pm::Integer& b) { return static_cast<long>(a) - b; })
        .method("-", [](int32_t a, pm::Integer& b) { return a - b; })
        // unary minus
        .method("-", [](pm::Integer& a) { return -a; })

        .method("div", [](pm::Integer& a, pm::Integer& b) { return a / b; })
        .method("div", [](pm::Integer& a,
                          int64_t b) { return a / static_cast<long>(b); })
        .method("div", [](pm::Integer& a, int32_t b) { return a / b; })
        .method("div",
                [](int64_t a, pm::Integer& b) {
                    return static_cast<long>(a) / b;
                })
        .method("div", [](int32_t a, pm::Integer& b) { return a / b; })

        .method("rem", [](pm::Integer& a, pm::Integer& b) { return a % b; })
        .method("rem", [](pm::Integer& a,
                          int64_t b) { return a % static_cast<long>(b); })
        .method("rem", [](pm::Integer& a, int32_t b) { return a % b; })
        .method("rem",
                [](int64_t a, pm::Integer& b) {
                    return static_cast<long>(a) % b;
                })
        .method("rem", [](int32_t a, pm::Integer& b) { return a % b; })
        .method("take", [](pm::perl::Object p, const std::string& s,
                           pm::Integer& a){p.take(s) << a;});

    polymake.method("new_pm_Integer_from_bigint", new_integer_from_bigint);
    polymake.method("to_pm_Integer", [](pm::perl::PropertyValue pv) {
        return to_SmallObject<pm::Integer>(pv);
    });
}
