// todo foss: tidying this up
// todo foss: pull in more M_MAKER stuff

#ifndef M_DEFINED
#define M_DEFINED

#ifndef M_LOGGER
#define M_LOGGER L_LOGV
#endif

#include "C.h"
#include "L.h"
#include "X.h"

// enum m_event_type_enum
// {
//     M_EVENT_TYPE_INVALID = 0,
//     M_EVENT_TYPE_INVALID_STATE,
//     M_EVENT_TYPE_ENTERING_STATE,
//     M_EVENT_TYPE_ENTERED_STATE,
//     M_EVENT_TYPE_LEAVING_STATE,
//     M_EVENT_TYPE_LEFT_STATE,
// };

#include "X.h"

#define X_ENUM_NAME m_event_type
#define X_ITEM_PREFIX M_EVENT_TYPE

#define X_ITEMS(X)                                                             \
    X(INVALID_STATE, )                                                         \
    X(ENTERING_STATE, )                                                        \
    X(ENTERED_STATE, )                                                         \
    X(LEAVING_STATE, )                                                         \
    X(LEFT_STATE, )

#ifdef M_IMPL
#define X_ENUM_IMPL
#include "X_enum.h"
#endif

#define M_STATE_TYPE(N) enum m_##N##_state_enum
#define M_TRIGGER_TYPE(N) enum m_##N##_trigger_enum
#define M_ACTION_TYPE(N) enum m_##N##_action_enum
#define M_TYPE(N) struct m_##N##_t
#define M_DISPATCHER_TYPE void *
#define M_CONTEXT_REMOVED_TYPE void *
#define M_ACTION_CALLBACK_TYPE(N)                                              \
    void (*action_callback)(enum m_##N##_action_enum)

#define M_STATE(N, S) M_##N##_##S##_STATE
#define M_STATE_INVALID 0
#define M_TRIGGER(N, T) M_##N##_##T##_TRIGGER
#define M_TRIGGER_NONE 0
#define M_ACTION(N, A) M_##N##_##A##_ACTION
#define M_ACTION_NONE 0

#define M_STATE_XX_T(N, S1, S2)                                                \
    M_STATE_TYPE(N){M_STATE(N, INVALID) = M_STATE_INVALID, M_STATE(N, S1),     \
                    M_STATE(N, S2)};

#define M_STATE_XXX_T(N, S1, S2, S3)                                           \
    M_STATE_TYPE(N){M_STATE(N, INVALID) = M_STATE_INVALID, M_STATE(N, S1),     \
                    M_STATE(N, S2), M_STATE(N, S3)};

#define M_STATE_XXXX_T(N, S1, S2, S3, S4)                                      \
    M_STATE_TYPE(N){M_STATE(N, INVALID) = M_STATE_INVALID, M_STATE(N, S1),     \
                    M_STATE(N, S2), M_STATE(N, S3), M_STATE(N, S4)};

#define M_STATE_XXXXX_T(N, S1, S2, S3, S4, S5)                                 \
    M_STATE_TYPE(N){M_STATE(N, INVALID) = M_STATE_INVALID,                     \
                    M_STATE(N, S1),                                            \
                    M_STATE(N, S2),                                            \
                    M_STATE(N, S3),                                            \
                    M_STATE(N, S4),                                            \
                    M_STATE(N, S5)};

#define M_TRIGGER_X_T(N, T1)                                                   \
    M_TRIGGER_TYPE(N){M_TRIGGER(N, NONE) = M_TRIGGER_NONE, M_TRIGGER(N, T1)};

#define M_TRIGGER_XX_T(N, T1, T2)                                              \
    M_TRIGGER_TYPE(N){M_TRIGGER(N, NONE) = M_TRIGGER_NONE, M_TRIGGER(N, T1),   \
                      M_TRIGGER(N, T2)};

#define M_TRIGGER_XXX_T(N, T1, T2, T3)                                         \
    M_TRIGGER_TYPE(N){M_TRIGGER(N, NONE) = M_TRIGGER_NONE, M_TRIGGER(N, T1),   \
                      M_TRIGGER(N, T2), M_TRIGGER(N, T3)};

#define M_TRIGGER_XXXX_T(N, T1, T2, T3, T4)                                    \
    M_TRIGGER_TYPE(N){M_TRIGGER(N, NONE) = M_TRIGGER_NONE, M_TRIGGER(N, T1),   \
                      M_TRIGGER(N, T2), M_TRIGGER(N, T3), M_TRIGGER(N, T4)};

#define M_ACTION_X_T(N, A1)                                                    \
    M_ACTION_TYPE(N){M_ACTION(N, NONE) = M_ACTION_NONE, M_ACTION(N, A1)};

#define M_ACTION_XX_T(N, A1, A2)                                               \
    M_ACTION_TYPE(N){M_ACTION(N, NONE) = M_ACTION_NONE, M_ACTION(N, A1),       \
                     M_ACTION(N, A2)};

#define M_ACTION_XXX_T(N, A1, A2, A3)                                          \
    M_ACTION_TYPE(N){M_ACTION(N, NONE) = M_ACTION_NONE, M_ACTION(N, A1),       \
                     M_ACTION(N, A2), M_ACTION(N, A3)};

#define M_T(N)                                                                 \
    M_TYPE(N)                                                                  \
    {                                                                          \
        M_STATE_TYPE(N) state;                                                 \
        M_STATE_TYPE(N) previous_state;                                        \
        M_STATE_TYPE(N) next_state;                                            \
        M_DISPATCHER_TYPE dispatcher;                                          \
        M_DISPATCHER_TYPE next_dispatcher;                                     \
        void (*action_callback)(M_TYPE(N) *, enum m_event_type_enum,           \
                                M_STATE_TYPE(N), M_CONTEXT_TYPE);              \
        M_CONTEXT_TYPE context;                                                \
    }

#define M_INIT(N, O, A, C)                                                     \
    {                                                                          \
        .dispatcher = 0, .state = M_STATE_INVALID, .next_dispatcher = 0,       \
        .previous_state = M_STATE_INVALID, .action_callback = A,               \
        .next_state = M_STATE_INVALID, .action_callback = A, .context = C,     \
    }

#define M_DISPATCH(N, O)                                                       \
    O->previous_state = O->state;                                              \
    DISPATCH:                                                                  \
    if (O->dispatcher)                                                         \
    {                                                                          \
        dispatcher = O->dispatcher;                                            \
        O->dispatcher = 0;                                                     \
        goto *dispatcher;                                                      \
    }

#define M_PHASE_ENTER(S) ENTER_##S
#define M_PHASE_OCCUPY(S) OCCUPY_##S
#define M_PHASE_LEAVE(S) LEAVE_##S
#define M_PHASE_GONE(S) GONE_##S

#define M_HAS_MOVED(O) (O->previous_state != O->state)

#define M_MOVE(O, S)                                                           \
    ({                                                                         \
        O->dispatcher = &&M_PHASE_ENTER(S);                                    \
        goto CRANK;                                                            \
    })
#define M_STAY(O, S)                                                           \
    ({                                                                         \
        O->dispatcher = &&M_PHASE_OCCUPY(S);                                   \
        goto CRANK;                                                            \
    })
#define M_DISPATCH_LEAVE(O, S)                                                 \
    ({                                                                         \
        O->dispatcher = &&M_PHASE_LEAVE(S);                                    \
        goto CRANK;                                                            \
    })
#define M_DISPATCH_LEAVE_AND_MOVE(O, S, N)                                     \
    ({                                                                         \
        O->dispatcher = &&M_PHASE_LEAVE(S);                                    \
        O->next_dispatcher = &&M_PHASE_ENTER(N);                               \
        goto CRANK;                                                            \
    })
#define M_GO(O, S)                                                             \
    ({                                                                         \
        O->dispatcher = &&M_PHASE_GONE(S);                                     \
        goto CRANK;                                                            \
    })

#define M_ENTER(N, O, S) M_PHASE_ENTER(S) : O->state = M_STATE(N, S);
#define M_OCCUPY(N, O, S) M_PHASE_OCCUPY(S)
#define M_LEAVE(N, O, S) M_PHASE_LEAVE(S)
#define M_GONE(N, O, S) M_PHASE_GONE(S)

#define RAISE(N, T, S)                                                         \
    if (fsm->action_callback)                                                  \
    {                                                                          \
        M_LOGGER("raising " #S " " #T);                                        \
        fsm->action_callback(fsm, T, M_MAKE_STATE(N, S), fsm->context);        \
    }

// #define MOVE_IF_MATCH_TRIGGER(N, O, T, S)                                         \
//     if (TRIGGER == TRIGGER(N, T))                                              \
//     {                                                                          \
//         M_LOGGER("moving to " #S);                           \
//         O->next_state = M_MAKE_STATE(N, S); \
//         M_DISPATCH_LEAVE(O, S);                                                               \
//     }

#define M_STATE_HANDLER(N, O, S, E, L, ...)                                    \
    M_ENTER(N, O, S)                                                           \
    {                                                                          \
        M_LOGGER("enter " #S);                                                 \
        RAISE(N, M_EVENT_TYPE_ENTERING_STATE, S);                              \
        E RAISE(N, M_EVENT_TYPE_ENTERED_STATE, S);                             \
    }                                                                          \
    M_OCCUPY(N, O, S) : if ((TRIGGER_NONE == TRIGGER)) M_STAY(O, S);           \
    C_RECURSE(C_FOREACH_XX_YY(MOVE_IF_TRIGGER, N, S, __VA_ARGS__))             \
    M_LOGGER("invalid state transition attempted, staying at " #S);            \
    RAISE(N, M_EVENT_TYPE_INVALID_STATE, INVALID)                              \
    M_STAY(O, S);                                                              \
    M_LEAVE(N, O, S) :                                                         \
    {                                                                          \
        M_LOGGER("leave " #S);                                                 \
        RAISE(N, M_EVENT_TYPE_LEAVING_STATE, S);                               \
        L RAISE(N, M_EVENT_TYPE_LEFT_STATE, S);                                \
        M_GO(O, S);                                                            \
    }                                                                          \
    M_GONE(N, O, S) :                                                          \
    {                                                                          \
        O->state = O->next_state;                                              \
        O->next_state = M_STATE_INVALID;                                       \
        O->dispatcher = O->next_dispatcher;                                    \
        O->next_dispatcher = 0;                                                \
        M_LOGGER("gone");                                                      \
        goto CRANK;                                                            \
    }

#define MOVE_IF_TRIGGER(N, S, T, X)                                            \
    if (TRIGGER == TRIGGER(N, T))                                              \
    {                                                                          \
        M_LOGGER("moving to " #X);                                             \
        fsm->next_state = M_MAKE_STATE(N, X);                                  \
        M_DISPATCH_LEAVE_AND_MOVE(fsm, S, X);                                  \
    }

// #define TRANSITIONS(N, ...)                                                    \
//     C_RECURSE(C_MAP2(MOVE_IF_TRIGGER, N, __VA_ARGS__))                         \
//     M_LOGGER("invalid state transition attempted");                            \
//     RAISE(N, M_EVENT_TYPE_INVALID_STATE, INVALID)

#define M_MAKE(N, O, I, C) M_FSM(N, O, I, C)
#define M_MAKE_TYPE(N) M_TYPE(N)
#define M_MAKE_T(N) M_T(N)
#define M_MAKE_TRIGGER_TYPE(N) M_TRIGGER_TYPE(N)
#define M_MAKE_TRIGGER(N, T) M_TRIGGER(N, T)
#define M_MAKE_ACTION_TYPE(N) M_ACTION_TYPE(N)
#define M_MAKE_ACTION(N, A) M_ACTION(N, A)

#define M_MAKE_STATE_TYPE(N) M_STATE_TYPE(N)
#define M_MAKE_STATE(N, S) M_STATE(N, S)

#define M_MAKE_STATE_XX_T(N, S1, S2) M_STATE_XX_T(N, S1, S2)
#define M_MAKE_STATE_XXX_T(N, S1, S2, S3) M_STATE_XXX_T(N, S1, S2, S3)
#define M_MAKE_STATE_XXXX_T(N, S1, S2, S3, S4) M_STATE_XXXX_T(N, S1, S2, S3, S4)
#define M_MAKE_STATE_XXXXX_T(N, S1, S2, S3, S4, S5)                            \
    M_STATE_XXXXX_T(N, S1, S2, S3, S4, S5)
#define M_MAKE_TRIGGER_X_T(N, T1) M_TRIGGER_X_T(N, T1)
#define M_MAKE_TRIGGER_XX_T(N, T1, T2) M_TRIGGER_XX_T(N, T1, T2)
#define M_MAKE_TRIGGER_XXX_T(N, T1, T2, T3) M_TRIGGER_XXX_T(N, T1, T2, T3)
#define M_MAKE_TRIGGER_XXXX_T(N, T1, T2, T3, T4)                               \
    M_TRIGGER_XXXX_T(N, T1, T2, T3, T4)
#define M_MAKE_ACTION_X_T(N, T1) M_ACTION_X_T(N, T1)
#define M_MAKE_ACTION_XX_T(N, T1, T2) M_ACTION_XX_T(N, T1, T2)
#define M_MAKE_ACTION_XXX_T(N, A1, A2, A3) M_ACTION_XXX_T(N, A1, A2, A3)

#define M_MAKE_STATE_HANDLER(N, O, S, E, L, ...)                               \
    M_STATE_HANDLER(N, O, S, E, L, __VA_ARGS__)
#define M_MAKE_DISPATCH(N, O) M_DISPATCH(N, O)

#define FSM(N, O, I, C) M_MAKE(N, O, I, C)
#define CONTEXT(O, T)                                                          \
    T CONTEXT = fsm->context;                                                  \
    (void)CONTEXT;
#define DISPATCH(O) M_MAKE_DISPATCH(N, O)
#define STATE_HANDLER(N, S, E, L, ...)                                         \
    M_MAKE_STATE_HANDLER(N, fsm, S, E, L, __VA_ARGS__)
#define TRIGGER(N, T) M_MAKE_TRIGGER(N, T)
#define STATE(N, S) M_MAKE_STATE(N, S)
#define ACTION(N, A) M_MAKE_ACTION(N, A)
#define MOVE(S) M_MOVE(fsm, S)

#define MATCH_ANY_TRIGGER (1)
#define MATCH_NO_TRIGGER (0)
#define MATCH_NONE_TRIGGER(N) (TRIGGER_NONE == TRIGGER)
#define MATCH_TRIGGER(N, T) (M_MAKE_TRIGGER(N, T) == TRIGGER)
#define MATCH_OR_NONE_TRIGGER(N, T)                                            \
    ((TRIGGER_NONE == TRIGGER) || MATCH_TRIGGER(N, T))
#define NOMATCH_TRIGGER(N, T) (M_MAKE_TRIGGER(N, T) != TRIGGER)
#define ANYBUT_TRIGGER(N, T)                                                   \
    ((TRIGGER_NONE != TRIGGER) && (M_MAKE_TRIGGER(N, T) != TRIGGER))

#define M_FSM(N, C)                                                            \
    _Pragma("GCC diagnostic push") _Pragma(                                    \
        "GCC diagnostic ignored \"-Wunused-label\"") static N##_state_type     \
        N##_fsm_move_next(N##_fsm_type *fsm, N##_trigger_type TRIGGER)         \
    {                                                                          \
        void *dispatcher = 0;                                                  \
        CONTEXT(fsm, N##_context_type);                                        \
        DISPATCH(fsm);                                                         \
        C CRANK : TRIGGER = TRIGGER_NONE;                                      \
        if (fsm->dispatcher && (fsm->dispatcher != dispatcher))                \
            goto DISPATCH;                                                     \
        return M_HAS_MOVED(fsm);                                               \
    }                                                                          \
    _Pragma("GCC diagnostic pop")

// todo crz: make these fit
#define M_CASE_ZERO_TO_INVALID                                                 \
    case 0:                                                                    \
        return "INVALID"
#define M_CASE_ID_TO_STRING(N)                                                 \
    case N:                                                                    \
        return #N
#define M_CASE_DEFAULT_TO_UNKNOWN                                              \
    default:                                                                   \
        return "UNKNOWN"

#define M_STATE_STRING_XX(N, S1, S2)                                           \
    static inline char const *N##_fsm_state_string(M_STATE_TYPE(N) state)      \
    {                                                                          \
        switch (state)                                                         \
        {                                                                      \
        case M_STATE(N, INVALID):                                              \
            return "INVALID";                                                  \
        case M_STATE(N, S1):                                                   \
            return #S1;                                                        \
        case M_STATE(N, S2):                                                   \
            return #S2;                                                        \
        }                                                                      \
        return "UNKNOWN";                                                      \
    }

#define M_STATE_STRING_XXX(N, S1, S2, S3)                                      \
    static inline char const *N##_fsm_state_string(M_STATE_TYPE(N) state)      \
    {                                                                          \
        switch (state)                                                         \
        {                                                                      \
        case M_STATE(N, INVALID):                                              \
            return "INVALID";                                                  \
        case M_STATE(N, S1):                                                   \
            return #S1;                                                        \
        case M_STATE(N, S2):                                                   \
            return #S2;                                                        \
        case M_STATE(N, S3):                                                   \
            return #S3;                                                        \
        }                                                                      \
        return "UNKNOWN";                                                      \
    }

#define M_STATE_STRING_XXXX(N, S1, S2, S3, S4)                                 \
    static inline char const *N##_fsm_state_string(M_STATE_TYPE(N) state)      \
    {                                                                          \
        switch (state)                                                         \
        {                                                                      \
        case M_STATE(N, INVALID):                                              \
            return "INVALID";                                                  \
        case M_STATE(N, S1):                                                   \
            return #S1;                                                        \
        case M_STATE(N, S2):                                                   \
            return #S2;                                                        \
        case M_STATE(N, S3):                                                   \
            return #S3;                                                        \
        case M_STATE(N, S4):                                                   \
            return #S4;                                                        \
        }                                                                      \
        return "UNKNOWN";                                                      \
    }

#define M_STATE_STRING_XXXXX(N, S1, S2, S3, S4, S5)                            \
    static inline char const *N##_fsm_state_string(M_STATE_TYPE(N) state)      \
    {                                                                          \
        switch (state)                                                         \
        {                                                                      \
        case M_STATE(N, INVALID):                                              \
            return "INVALID";                                                  \
        case M_STATE(N, S1):                                                   \
            return #S1;                                                        \
        case M_STATE(N, S2):                                                   \
            return #S2;                                                        \
        case M_STATE(N, S3):                                                   \
            return #S3;                                                        \
        case M_STATE(N, S4):                                                   \
            return #S4;                                                        \
        case M_STATE(N, S5):                                                   \
            return #S5;                                                        \
        }                                                                      \
        return "UNKNOWN";                                                      \
    }

#define M_MAKE_STATE_STRING_XX(N, S1, S2) M_STATE_STRING_XX(N, S1, S2)
#define M_MAKE_STATE_STRING_XXX(N, S1, S2, S3) M_STATE_STRING_XXX(N, S1, S2, S3)
#define M_MAKE_STATE_STRING_XXXX(N, S1, S2, S3, S4)                            \
    M_STATE_STRING_XXXX(N, S1, S2, S3, S4)
#define M_MAKE_STATE_STRING_XXXXX(N, S1, S2, S3, S4, S5)                       \
    M_STATE_STRING_XXXXX(N, S1, S2, S3, S4, S5)

#define M_TRIGGER_STRING_X(N, T1)                                              \
    static inline char const *N##_fsm_trigger_string(M_TRIGGER_TYPE(N)         \
                                                         trigger)              \
    {                                                                          \
        switch (trigger)                                                       \
        {                                                                      \
        case M_TRIGGER(N, NONE):                                               \
            return "NONE";                                                     \
        case M_TRIGGER(N, T1):                                                 \
            return #T1;                                                        \
        }                                                                      \
        return "UNKNOWN";                                                      \
    }

#define M_TRIGGER_STRING_XX(N, T1, T2)                                         \
    static inline char const *N##_fsm_trigger_string(M_TRIGGER_TYPE(N)         \
                                                         trigger)              \
    {                                                                          \
        switch (trigger)                                                       \
        {                                                                      \
        case M_TRIGGER(N, NONE):                                               \
            return "NONE";                                                     \
        case M_TRIGGER(N, T1):                                                 \
            return #T1;                                                        \
        case M_TRIGGER(N, T2):                                                 \
            return #T2;                                                        \
        }                                                                      \
        return "UNKNOWN";                                                      \
    }

#define M_TRIGGER_STRING_XXX(N, T1, T2, T3)                                    \
    static inline char const *N##_fsm_trigger_string(M_TRIGGER_TYPE(N)         \
                                                         trigger)              \
    {                                                                          \
        switch (trigger)                                                       \
        {                                                                      \
        case M_TRIGGER(N, NONE):                                               \
            return "NONE";                                                     \
        case M_TRIGGER(N, T1):                                                 \
            return #T1;                                                        \
        case M_TRIGGER(N, T2):                                                 \
            return #T2;                                                        \
        case M_TRIGGER(N, T3):                                                 \
            return #T3;                                                        \
        }                                                                      \
        return "UNKNOWN";                                                      \
    }

#define M_TRIGGER_STRING_XXXX(N, T1, T2, T3, T4)                               \
    static inline char const *N##_fsm_trigger_string(M_TRIGGER_TYPE(N)         \
                                                         trigger)              \
    {                                                                          \
        switch (trigger)                                                       \
        {                                                                      \
        case M_TRIGGER(N, NONE):                                               \
            return "NONE";                                                     \
        case M_TRIGGER(N, T1):                                                 \
            return #T1;                                                        \
        case M_TRIGGER(N, T2):                                                 \
            return #T2;                                                        \
        case M_TRIGGER(N, T3):                                                 \
            return #T3;                                                        \
        case M_TRIGGER(N, T4):                                                 \
            return #T4;                                                        \
        }                                                                      \
        return "UNKNOWN";                                                      \
    }

#define M_MAKE_TRIGGER_STRING_X(N, T1) M_TRIGGER_STRING_X(N, T1)
#define M_MAKE_TRIGGER_STRING_XX(N, T1, T2) M_TRIGGER_STRING_XX(N, T1, T2)
#define M_MAKE_TRIGGER_STRING_XXX(N, T1, T2, T3)                               \
    M_TRIGGER_STRING_XXX(N, T1, T2, T3)
#define M_MAKE_TRIGGER_STRING_XXXX(N, T1, T2, T3, T4)                          \
    M_TRIGGER_STRING_XXXX(N, T1, T2, T3, T4)

#define M_ACTION_STRING_X(N, A1)                                               \
    static inline char const *N##_fsm_action_string(M_ACTION_TYPE(N) action)   \
    {                                                                          \
        switch (action)                                                        \
        {                                                                      \
        case M_ACTION(N, NONE):                                                \
            return "NONE";                                                     \
        case M_ACTION(N, A1):                                                  \
            return #A1;                                                        \
        }                                                                      \
        return "UNKNOWN";                                                      \
    }

#define M_ACTION_STRING_XX(N, A1, A2)                                          \
    static inline char const *N##_fsm_action_string(M_ACTION_TYPE(N) action)   \
    {                                                                          \
        switch (action)                                                        \
        {                                                                      \
        case M_ACTION(N, NONE):                                                \
            return "NONE";                                                     \
        case M_ACTION(N, A1):                                                  \
            return #A1;                                                        \
        case M_ACTION(N, A2):                                                  \
            return #A2;                                                        \
        }                                                                      \
        return "UNKNOWN";                                                      \
    }

#define M_ACTION_STRING_XXX(N, A1, A2, A3)                                     \
    static inline char const *N##_fsm_action_string(M_ACTION_TYPE(N) action)   \
    {                                                                          \
        switch (action)                                                        \
        {                                                                      \
        case M_ACTION(N, NONE):                                                \
            return "NONE";                                                     \
        case M_ACTION(N, A1):                                                  \
            return #A1;                                                        \
        case M_ACTION(N, A2):                                                  \
            return #A2;                                                        \
        case M_ACTION(N, A3):                                                  \
            return #A3;                                                        \
        }                                                                      \
        return "UNKNOWN";                                                      \
    }

#define M_MAKE_ACTION_STRING_X(N, A1) M_ACTION_STRING_X(N, A1)
#define M_MAKE_ACTION_STRING_XX(N, A1, A2) M_ACTION_STRING_XX(N, A1, A2)
#define M_MAKE_ACTION_STRING_XXX(N, A1, A2, A3)                                \
    M_ACTION_STRING_XXX(N, A1, A2, A3)

#define TRIGGER_NONE M_TRIGGER_NONE
#define ACTION_NONE M_ACTION_NONE

#endif

#ifdef M_NAME

#ifndef M_CONTEXT_TYPE
#define M_CONTEXT_TYPE M_CONTEXT_REMOVED_TYPE
#endif

#ifndef M_STATE_5
#ifndef M_STATE_4
#ifndef M_STATE_3
#ifndef M_STATE_2
#error M ERROR: there must be at least 2 states
#else
M_MAKE_STATE_XX_T(M_NAME, M_STATE_1, M_STATE_2);
M_MAKE_STATE_STRING_XX(M_NAME, M_STATE_1, M_STATE_2)
#endif
#else
M_MAKE_STATE_XXX_T(M_NAME, M_STATE_1, M_STATE_2, M_STATE_3);
M_MAKE_STATE_STRING_XXX(M_NAME, M_STATE_1, M_STATE_2, M_STATE_3)
#endif
#else
M_MAKE_STATE_XXXX_T(M_NAME, M_STATE_1, M_STATE_2, M_STATE_3, M_STATE_4);
M_MAKE_STATE_STRING_XXXX(M_NAME, M_STATE_1, M_STATE_2, M_STATE_3, M_STATE_4);
#endif
#else
M_MAKE_STATE_XXXXX_T(M_NAME, M_STATE_1, M_STATE_2, M_STATE_3, M_STATE_4,
                     M_STATE_5);
M_MAKE_STATE_STRING_XXXXX(M_NAME, M_STATE_1, M_STATE_2, M_STATE_3, M_STATE_4,
                          M_STATE_5);
#endif

#ifndef M_TRIGGER_4
#ifndef M_TRIGGER_3
#ifndef M_TRIGGER_2
#ifndef M_TRIGGER_1
#else
M_MAKE_TRIGGER_X_T(M_NAME, M_TRIGGER_1);
M_MAKE_TRIGGER_STRING_X(M_NAME, M_TRIGGER_1);
#endif
#else
M_MAKE_TRIGGER_XX_T(M_NAME, M_TRIGGER_1, M_TRIGGER_2);
M_MAKE_TRIGGER_STRING_XX(M_NAME, M_TRIGGER_1, M_TRIGGER_2);
#endif
#else
M_MAKE_TRIGGER_XXX_T(M_NAME, M_TRIGGER_1, M_TRIGGER_2, M_TRIGGER_3);
M_MAKE_TRIGGER_STRING_XXX(M_NAME, M_TRIGGER_1, M_TRIGGER_2, M_TRIGGER_3);
#endif
#else
M_MAKE_TRIGGER_XXXX_T(M_NAME, M_TRIGGER_1, M_TRIGGER_2, M_TRIGGER_3,
                      M_TRIGGER_4);
M_MAKE_TRIGGER_STRING_XXXX(M_NAME, M_TRIGGER_1, M_TRIGGER_2, M_TRIGGER_3,
                           M_TRIGGER_4);
#endif

#ifndef M_ACTION_3
#ifndef M_ACTION_2
#ifndef M_ACTION_1
#else
M_MAKE_ACTION_X_T(M_NAME, M_ACTION_1);
M_MAKE_ACTION_STRING_X(M_NAME, M_ACTION_1)
#endif
#else
M_MAKE_ACTION_XX_T(M_NAME, M_ACTION_1, M_ACTION_2);
M_MAKE_ACTION_STRING_XX(M_NAME, M_ACTION_1, M_ACTION_2)
#endif
#else
M_MAKE_ACTION_XXX_T(M_NAME, M_ACTION_1, M_ACTION_2, M_ACTION_3);
M_MAKE_ACTION_STRING_XXX(M_NAME, M_ACTION_1, M_ACTION_2, M_ACTION_3);
#endif

#define ___M_PREFIX(X, N) X##_##N
#define __M_PREFIX(X, N) ___M_PREFIX(X, N)
#define _M_PREFIX(N) __M_PREFIX(M_NAME, N)
#define M_PREFIX(N) _M_PREFIX(N)

typedef M_MAKE_STATE_TYPE(M_NAME) M_PREFIX(state_type);
typedef M_MAKE_TRIGGER_TYPE(M_NAME) M_PREFIX(trigger_type);
typedef M_MAKE_ACTION_TYPE(M_NAME) M_PREFIX(action_type);
typedef M_CONTEXT_TYPE M_PREFIX(context_type);
typedef M_MAKE_TYPE(M_NAME) M_PREFIX(fsm_type);
typedef void (*M_PREFIX(action_callback_type))(M_PREFIX(action_type));
typedef M_MAKE_T(M_NAME) M_PREFIX(fsm_t);

#undef M_NAME
#undef M_CONTEXT_TYPE
#undef M_STATE_1
#undef M_STATE_2
#undef M_STATE_3
#undef M_STATE_4
#undef M_STATE_5
#undef M_TRIGGER_1
#undef M_TRIGGER_2
#undef M_TRIGGER_3
#undef M_TRIGGER_4
#undef M_ACTION_1
#undef M_ACTION_2
#undef M_ACTION_3
#undef M_ACTION_4
#endif
