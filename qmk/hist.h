#pragma once

#include "stroke.h"

#define HIST_SIZE 30

/* typedef struct __attribute__((packed)) { */
/*     uint32_t stroke : 24; */
/*     uint32_t node : 24; */
/*     uint8_t replaced; */
/* } history_t; */

typedef enum {
    RAW_STROKE,
    NODE_STRING,
} output_type_t;

typedef struct __attribute__((packed)) {
    output_type_t type;
    union {
        uint32_t stroke : 24;
        uint32_t node : 24;
    };
} output_t;

typedef struct __attribute__((packed)) {
    uint8_t space : 1;
    uint8_t cap : 1;
    uint8_t prev_glue : 1;
} state_t;

typedef struct __attribute__((packed)) {
    uint8_t len;
    uint8_t repl_len;
    state_t state;
    uint8_t search_nodes_len;
    search_node_t *search_nodes;
    output_t output;
} history_t;

extern search_node_t search_nodes[SEARCH_NODES_SIZE];
extern uint8_t search_nodes_len;
extern state_t state;

void hist_add(history_t hist);
void hist_undo(void);
uint8_t process_output(state_t *state, output_t output, uint8_t repl_len);