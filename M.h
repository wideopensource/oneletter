#ifndef M_DEFINED
#define M_DEFINED

#include "C.h"
#include "L.h"
#include "X.h"

#ifndef M_LOGE
#define M_LOGE(...) L_LOGE(__VA_ARGS__)
#endif

#ifndef M_LOGW
#define M_LOGW(...) L_LOGW(__VA_ARGS__)
#endif

#ifndef M_LOGI
#define M_LOGI(...) L_LOGI(__VA_ARGS__)
#endif

#ifndef M_LOGD
#define M_LOGD(...) L_LOGD(__VA_ARGS__)
#endif

#ifndef M_LOGV
#define M_LOGV(...) L_LOGV(__VA_ARGS__)
#endif

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
#endif
#include "X_enum.h"

#define X_ITEMS M_STATES
#define X_ENUM_NAME M_STATES_ENUM_NAME
#define X_ITEM_PREFIX M_STATES_ITEM_PREFIX

#ifdef M_IMPL
#define X_ENUM_IMPL
#endif
#include "X_enum.h"

#define X_ITEMS M_TRIGGERS
#define X_ENUM_NAME M_TRIGGERS_ENUM_NAME
#define X_ITEM_PREFIX M_TRIGGERS_ITEM_PREFIX

#ifdef M_IMPL
#define X_ENUM_IMPL
#endif
#include "X_enum.h"

#define M_STATE_TYPE(N) enum m_##N##_state_enum
#define M_TRIGGER_TYPE(N) enum m_##N##_trigger_enum
#define M_ACTION_TYPE(N) enum m_##N##_action_enum
#define M_TYPE(N) struct m_##N##_t
#define M_DISPATCHER_TYPE void *
#define M_CONTEXT_REMOVED_TYPE void *
#define M_ACTION_CALLBACK_TYPE(N)                                              \
    void (*action_callback)(enum m_##N##_action_enum)

#define M_STATE(N, S) M_##N##_FSM_STATE_##S
#define M_STATE_INVALID 0
#define M_TRIGGER(N, T) M_##N##_FSM_TRIGGER_##T
#define M_TRIGGER_NONE 0
#define M_ACTION(N, A) M_##N##_##A##_ACTION
#define M_ACTION_NONE 0

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

#define M_INIT(A, C)                                                           \
    {                                                                          \
        .state = M_STATE_INVALID, .previous_state = M_STATE_INVALID,           \
        .next_state = M_STATE_INVALID, .dispatcher = 0, .next_dispatcher = 0,  \
        .action_callback = A, .context = C                                     \
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
        M_LOGV("raising " #S " " #T);                                          \
        fsm->action_callback(fsm, T, M_MAKE_STATE(N, S), fsm->context);        \
    }

#define M_STATE_HANDLER(N, O, S, E, C, L, ...)                                 \
    M_ENTER(N, O, S)                                                           \
    {                                                                          \
        M_LOGV("enter " #S);                                                   \
        RAISE(N, M_EVENT_TYPE_ENTERING_STATE, S);                              \
        E RAISE(N, M_EVENT_TYPE_ENTERED_STATE, S);                             \
    }                                                                          \
    M_OCCUPY(N, O, S) : if ((TRIGGER_NONE == TRIGGER))                         \
    {                                                                          \
        C M_STAY(O, S);                                                        \
    }                                                                          \
    C_RECURSE(C_FOREACH_XX_YY(MOVE_IF_TRIGGER, N, S, __VA_ARGS__))             \
    M_LOGW("invalid trigger '%d', staying at " #S, TRIGGER);              \
    RAISE(N, M_EVENT_TYPE_INVALID_STATE, INVALID)                              \
    M_STAY(O, S);                                                              \
    M_LEAVE(N, O, S) :                                                         \
    {                                                                          \
        M_LOGV("leave " #S);                                                   \
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
        M_LOGV("gone");                                                        \
        goto CRANK;                                                            \
    }

#define MOVE_IF_TRIGGER(N, S, T, X)                                            \
    if (TRIGGER == TRIGGER(N, T))                                              \
    {                                                                          \
        M_LOGV("moving to " #X);                                               \
        fsm->next_state = M_MAKE_STATE(N, X);                                  \
        M_DISPATCH_LEAVE_AND_MOVE(fsm, S, X);                                  \
    }

#define M_MAKE(N, O, I, C) M_FSM(N, O, I, C)
#define M_MAKE_TYPE(N) M_TYPE(N)
#define M_MAKE_T(N) M_T(N)
#define M_MAKE_TRIGGER_TYPE(N) M_TRIGGER_TYPE(N)
#define M_MAKE_TRIGGER(N, T) M_TRIGGER(N, T)
#define M_MAKE_ACTION_TYPE(N) M_ACTION_TYPE(N)
#define M_MAKE_ACTION(N, A) M_ACTION(N, A)

#define M_MAKE_STATE_TYPE(N) M_STATE_TYPE(N)
#define M_MAKE_STATE(N, S) M_STATE(N, S)

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

#define FROM_MOVE_TO(S, X) M_DISPATCH_LEAVE_AND_MOVE(fsm, S, X)

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
    _Pragma("GCC diagnostic push")                                             \
        _Pragma("GCC diagnostic ignored \"-Wunused-label\"") static C_CONCAT(  \
            N, _state_type)                                                    \
            C_CONCAT(N, _fsm_move_next)(C_CONCAT(N, _fsm_type) * fsm,          \
                                        C_CONCAT(N, _trigger_type) TRIGGER)    \
    {                                                                          \
        void *dispatcher = 0;                                                  \
        CONTEXT(fsm, C_CONCAT(N, _context_type));                              \
        DISPATCH(fsm);                                                         \
        C CRANK : TRIGGER = TRIGGER_NONE;                                      \
        if (fsm->dispatcher && (fsm->dispatcher != dispatcher))                \
            goto DISPATCH;                                                     \
        return M_HAS_MOVED(fsm);                                               \
    }                                                                          \
    _Pragma("GCC diagnostic pop")

#define TRIGGER_NONE M_TRIGGER_NONE
#define ACTION_NONE M_ACTION_NONE

#endif

#ifdef M_NAME

#ifndef M_CONTEXT_TYPE
#define M_CONTEXT_TYPE M_CONTEXT_REMOVED_TYPE
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
#endif
