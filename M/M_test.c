#include <assert.h>
#include <stdio.h>


#define L_LIB_TAG M
#define L_LOG_TAG test
#define CONFIG_L_PLATFORM_POSIX 1

#define L_IMPL
#include "L.h"

#define X_IMPL
#include "X.h"

#define TEST_FSM_NAME test

struct context_t
{
};

#define M_NAME TEST_FSM_NAME
#define M_CONTEXT_TYPE struct context_t *

#define M_STATES(X)                                                            \
    X(STATE1, )                                                                \
    X(STATE2, )                                                                \
    X(STATE3, )                                                                \
    X(STATE4, )

#define M_STATES_ENUM_NAME m_test_state
#define M_STATES_ITEM_PREFIX M_test_FSM_STATE

#define M_TRIGGERS(X)                                                          \
    X(NONE, )                                                                  \
    X(TRIGGER1, )                                                              \
    X(TRIGGER2, )                                                              \
    X(TRIGGER3, )                                                              \
    X(TRIGGER4, )                                                              \
    X(TRIGGER5, )

#define M_TRIGGERS_ENUM_NAME m_test_trigger
#define M_TRIGGERS_ITEM_PREFIX M_test_FSM_TRIGGER

#define M_IMPL
#include "M.h"

// clang-format off

M_FSM(TEST_FSM_NAME,
    STATE_HANDLER(TEST_FSM_NAME, STATE1,
    {
        L_LOGI("> enter STATE1");
    }, 
    {
        L_LOGI("= occupy STATE1");
    }, 
    {
        L_LOGI("< leave STATE1");
    }, 
        TRIGGER2, STATE2, TRIGGER3, STATE3, TRIGGER4, STATE4)
    STATE_HANDLER(TEST_FSM_NAME, STATE2, , , , TRIGGER1, STATE3)
    STATE_HANDLER(TEST_FSM_NAME, STATE3, , , , TRIGGER1, STATE2, TRIGGER4, STATE1)
    STATE_HANDLER(TEST_FSM_NAME, STATE4, , , , )
)

// clang-format on

static void event_callback(test_fsm_type *fsm,
                           enum m_event_type_enum event_type,
                           enum m_test_state_enum state,
                           struct context_t *context)
{
    L_LOGI("event_callback %s: %s->%s->%s\n",
           m_event_type_to_string(event_type),
           m_test_state_to_string(fsm->previous_state),
           m_test_state_to_string(fsm->state),
           m_test_state_to_string(fsm->next_state));
}

int main()
{
    struct context_t context;

    test_fsm_type fsm = M_INIT(event_callback, &context);

    test_state_type state = M_STATE_INVALID;

    int d = 0;

    L_LOGI(">> %d trigger NONE", ++d);
    state = test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, NONE));
    assert(M_MAKE_STATE(test, STATE1) == fsm.state);

    L_LOGI(">> %d trigger 4", ++d);
    test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER5));
    assert(M_MAKE_STATE(test, STATE1) == fsm.state);

    L_LOGI(">> %d trigger 3", ++d);
    test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER3));
    assert(M_MAKE_STATE(test, STATE3) == fsm.state);

    L_LOGI(">> %d trigger 2 in state %s", ++d, m_test_state_to_string(fsm.state));
    test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER2));
    assert(M_MAKE_STATE(test, STATE3) == fsm.state);

    L_LOGI(">> %d trigger 1", ++d);
    test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER1));
    assert(M_MAKE_STATE(test, STATE2) == fsm.state);

    L_LOGI(">> %d trigger NONE", ++d);
    state = test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, NONE));
    assert(M_MAKE_STATE(test, STATE2) == fsm.state);

    L_LOGI(">> %d trigger 1", ++d);
    test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER1));
    assert(M_MAKE_STATE(test, STATE3) == fsm.state);

    L_LOGI(">> %d trigger 1", ++d);
    test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER1));
    assert(M_MAKE_STATE(test, STATE2) == fsm.state);

    L_LOGI(">> %d trigger 3", ++d);
    test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER3));
    assert(M_MAKE_STATE(test, STATE2) == fsm.state);

    L_LOGI(">> %d trigger 1", ++d);
    test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER1));
    assert(M_MAKE_STATE(test, STATE3) == fsm.state);

    L_LOGI(">> %d trigger 4", ++d);
    test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER4));
    assert(M_MAKE_STATE(test, STATE1) == fsm.state);

    L_LOGI(">> %d trigger 4", ++d);
    test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER4));
    assert(M_MAKE_STATE(test, STATE4) == fsm.state);

    L_LOGI(">> done: %s", m_test_state_to_string(fsm.state));

    return 0;
}