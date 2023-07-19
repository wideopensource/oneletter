#define C_CONCAT(A, B) A##B
#define C_CONCAT3(A, B, C) A##B##C

#define __C_STRINGISE(S) #S
#define C_STRINGISE(S) __C_STRINGISE(S)

#define C_FIRST(ARG1, ...) ARG1
#define C_SECOND(ARG1, ARG2, ...) ARG2
#define C_THIRD(ARG1, ARG2, ARG3, ...) ARG3

#define __C_HAS_ONE_ARG_PROBE() __DUMMY, 1
#define __C_HAS_ONE_ARG(...) C_SECOND(__VA_ARGS__, 0)

#define __C_NOT_0 __C_HAS_ONE_ARG_PROBE()
#define __C_NOT(B) __C_HAS_ONE_ARG(C_CONCAT(__C_NOT_, B))
#define C_BOOL(B) __C_NOT(__C_NOT(B))

#define __C_RECURSE10(...) __VA_ARGS__
#define __C_RECURSE9(...) __C_RECURSE10(__C_RECURSE10(__VA_ARGS__))
#define __C_RECURSE8(...) __C_RECURSE9(__C_RECURSE9(__VA_ARGS__))
#define __C_RECURSE7(...) __C_RECURSE8(__C_RECURSE8(__VA_ARGS__))
#define __C_RECURSE6(...) __C_RECURSE7(__C_RECURSE7(__VA_ARGS__))
#define __C_RECURSE5(...) __C_RECURSE6(__C_RECURSE6(__VA_ARGS__))
#define __C_RECURSE4(...) __C_RECURSE5(__C_RECURSE5(__VA_ARGS__))
#define __C_RECURSE3(...) __C_RECURSE4(__C_RECURSE4(__VA_ARGS__))
#define __C_RECURSE2(...) __C_RECURSE3(__C_RECURSE3(__VA_ARGS__))
#define __C_RECURSE1(...) __C_RECURSE2(__C_RECURSE2(__VA_ARGS__))
#define C_RECURSE(...) __C_RECURSE1(__VA_ARGS__)

#define __C_NOP()
#define __C_DEFER1(O) O __C_NOP()
#define __C_DEFER2(O) O __C_NOP __C_NOP()()
#define __C_DEFER3(O) O __C_NOP __C_NOP __C_NOP()()()
#define __C_DEFER4(O) O __C_NOP __C_NOP __C_NOP __C_NOP()()()()

#define __C_IF_1_ELSE(...)
#define __C_IF_0_ELSE(...) __VA_ARGS__
#define __C_IF_1(...) __VA_ARGS__ __C_IF_1_ELSE
#define __C_IF_0(...) __C_IF_0_ELSE
#define __C_IF_ELSE(B) C_CONCAT(__C_IF_, B)
#define C_IF_ELSE(P) __C_IF_ELSE(C_BOOL(P))

#define __C_ARG_TERMINATOR() 0
#define __C_HAS_ARGS(...) C_BOOL(C_FIRST(__C_ARG_TERMINATOR __VA_ARGS__)())

#define __C_FOREACH_Y() C_FOREACH_Y
#define __C_FOREACH_X_YY() C_FOREACH_X_YY
#define __C_FOREACH_XX_YY() _C_FOREACH_XX_YY

#define C_FOREACH_Y(M, ARG1, ...)                                              \
    M(ARG1)                                                                    \
    C_IF_ELSE(__C_HAS_ARGS(__VA_ARGS__))                                       \
    (__C_DEFER2(__C_FOREACH_Y)()(M, __VA_ARGS__))()

#define C_FOREACH_X_YY(M, N, ARG1, ARG2, ...)                                  \
    M(N, ARG1, ARG2)                                                           \
    C_IF_ELSE(__C_HAS_ARGS(__VA_ARGS__))                                       \
    (__C_DEFER2(__C_FOREACH_X_YY)()(M, N, __VA_ARGS__))()

#define _C_FOREACH_XX_YY(M, N, O, ARG1, ARG2, ...)                             \
    M(N, O, ARG1, ARG2)                                                        \
    C_IF_ELSE(__C_HAS_ARGS(__VA_ARGS__))                                       \
    (__C_DEFER2(__C_FOREACH_XX_YY)()(M, N, O, __VA_ARGS__))()

#define C_FOREACH_XX_YY(M, N, O, ...)                                          \
    C_IF_ELSE(__C_HAS_ARGS(__VA_ARGS__))                                       \
    (__C_DEFER2(_C_FOREACH_XX_YY)(M, N, O, __VA_ARGS__))()
