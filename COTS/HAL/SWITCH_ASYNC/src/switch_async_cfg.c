#include "switch_async_cfg.h"

SwitchAsync_stSwitchCfg_t SwitchAsync_arr_SWitchCfgs[NO_OF_SWITCHES] = {

    [SWITCH1] = {
        .Port = GPIO_enu_GPIOA,
        .Pin = GPIO_enu_PIN4,
        .InputType = GPIO_enu_PD
    },

    [SWITCH2] = {
        .Port = GPIO_enu_GPIOA,
        .Pin = GPIO_enu_PIN4,
        .InputType = GPIO_enu_PD
    },

    [SWITCH3] = {
        .Port = GPIO_enu_GPIOA,
        .Pin = GPIO_enu_PIN4,
        .InputType = GPIO_enu_PU
    }
};