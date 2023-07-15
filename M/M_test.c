#include <stdio.h>
#include <assert.h>

#define L_LIB_TAG M
#define L_LOG_TAG test
#define CONFIG_L_PLATFORM_POSIX 1

#define L_IMPL
#include "L.h"

#define X_IMPL
#include "X.h"

struct context_t
{
};

#define M_NAME test
#define M_CONTEXT_TYPE struct context_t *
#define M_STATE_1 STATE1
#define M_STATE_2 STATE2
#define M_STATE_3 STATE3
#define M_TRIGGER_1 TRIGGER1
#define M_TRIGGER_2 TRIGGER2
#define M_TRIGGER_3 TRIGGER3
#define M_TRIGGER_4 TRIGGER4
// #define M_ACTION_1 ACTION1
// #define M_ACTION_2 ACTION2
// #define M_ACTION_3 ACTION3
// #define M_ACTION_4 ACTION4

#define M_IMPL
#include "M.h"

static void event_callback(test_fsm_type *fsm,
                           enum m_event_type_enum event_type,
                           enum m_test_state_enum state,
                           struct context_t *context)
{
    L_LOGI("event_callback %s: %s->%s->%s\n",
        m_event_type_to_string(event_type),
           test_fsm_state_string(fsm->previous_state),
           test_fsm_state_string(fsm->state),
           test_fsm_state_string(fsm->next_state)
           );
}

M_FSM(test,
    STATE_HANDLER(test, STATE1, , , TRIGGER2, STATE2, TRIGGER3, STATE3)
    STATE_HANDLER(test, STATE2, , , TRIGGER1, STATE3)
    STATE_HANDLER(test, STATE3, , , TRIGGER1, STATE2, TRIGGER4, STATE1)
)

int main()
{
    struct context_t context;

    test_fsm_type fsm = M_INIT(test, fsm, event_callback, &context);

    test_state_type state = M_STATE_INVALID;

    for (int i = 0; i < 100; ++i)
    {
        L_LOGI(">> trigger NONE");
        state = test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, NONE));
        assert(M_MAKE_STATE(test, STATE1) == fsm.state);

        L_LOGI(">> trigger 4");
        test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER4));
        assert(M_MAKE_STATE(test, STATE1) == fsm.state);

        L_LOGI(">> trigger 3");
        test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER3));
        assert(M_MAKE_STATE(test, STATE3) == fsm.state);

        L_LOGI(">> trigger 2 in state %s", test_fsm_state_string(fsm.state));
        test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER2));
        assert(M_MAKE_STATE(test, STATE3) == fsm.state);

        L_LOGI(">> trigger 1");
        test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER1));
        assert(M_MAKE_STATE(test, STATE2) == fsm.state);

        L_LOGI(">> trigger NONE");
        state = test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, NONE));
        assert(M_MAKE_STATE(test, STATE2) == fsm.state);

        L_LOGI(">> trigger 1");
        test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER1));
        assert(M_MAKE_STATE(test, STATE3) == fsm.state);

        L_LOGI(">> trigger 1");
        test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER1));
        assert(M_MAKE_STATE(test, STATE2) == fsm.state);

        L_LOGI(">> trigger 3");
        test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER3));
        assert(M_MAKE_STATE(test, STATE2) == fsm.state);

        L_LOGI(">> trigger 1");
        test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER1));
        assert(M_MAKE_STATE(test, STATE3) == fsm.state);

        L_LOGI(">> trigger 4");
        test_fsm_move_next(&fsm, M_MAKE_TRIGGER(test, TRIGGER4));
        assert(M_MAKE_STATE(test, STATE1) == fsm.state);
    }
    
    L_LOGI(">> done: %s", test_fsm_state_string(fsm.state));

    return 0;
}