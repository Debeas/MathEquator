#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "..\me_structure_blueprint.h"

/* ── Minimal stubs so the test file compiles stand-alone ───────────────────
   Remove these and #include your real headers once you link everything.     */

// #define MP_DEFAULT_START_WIDTH  10
// #define MP_DEFAULT_START_HEIGHT 10

// typedef enum { SINGLE_CHARACTER, ALPHABETIC } special_structure;
// typedef int (*CHECK_FUNC_T)(char*);


/* Forward declarations (implemented in your .c file) */
math_structure_blueprint_set_t* math_structure_blueprint_set_create(void);
math_structure_blueprint_set_t* math_structure_blueprint_set_defining(void);
void math_structure_blueprint_set_free(math_structure_blueprint_set_t*);
void math_structure_blueprint_set_test_print(math_structure_blueprint_set_t*);
void math_structure_blueprint_set_append(
    math_structure_blueprint_set_t*, char*, char*, char*,
    int, int, delta_xy_t*, CHECK_FUNC_T, enum special_structure);
struct delta_xy* delta_xy_create_first(int, int, int);
struct delta_xy* delta_xy_append(struct delta_xy*, int, int, int);
void             delta_xy_free(struct delta_xy*);
int              cf_alphabetic_singular(char*);

/* ── Test helpers ──────────────────────────────────────────────────────── */

static int tests_run    = 0;
static int tests_passed = 0;

#define TEST(name) \
    do { printf("\n[TEST] %s\n", name); tests_run++; } while(0)

#define EXPECT(cond) \
    do { \
        if (cond) { \
            printf("  PASS: %s\n", #cond); \
            tests_passed++; \
        } else { \
            printf("  FAIL: %s  (line %d)\n", #cond, __LINE__); \
        } \
    } while(0)

/* ── Individual tests ──────────────────────────────────────────────────── */

/* 1. delta_xy_create_first */
static void test_delta_xy_create_first(void) {
    TEST("delta_xy_create_first");

    delta_xy_t* d = delta_xy_create_first(3, 7, 20);
    printf("The length is %d\n", d->length);
    EXPECT(d != NULL);
    EXPECT(d->length == 1);
    EXPECT(d->dx[0]     == 3);
    EXPECT(d->dy[0]     == 7);
    EXPECT(d->height[0] == 20);

    delta_xy_free(d);
}

/* 2. delta_xy_append */
static void test_delta_xy_append(void) {
    TEST("delta_xy_append");

    delta_xy_t* d = delta_xy_create_first(1, 2, 10);
    delta_xy_append(d, 3, 4, 20);
    delta_xy_append(d, 5, 6, 30);

    EXPECT(d->length    == 3);
    EXPECT(d->dx[0]     == 1);
    EXPECT(d->dy[0]     == 2);
    EXPECT(d->height[0] == 10);
    EXPECT(d->dx[1]     == 3);
    EXPECT(d->dy[1]     == 4);
    EXPECT(d->height[1] == 20);
    EXPECT(d->dx[2]     == 5);
    EXPECT(d->dy[2]     == 6);
    EXPECT(d->height[2] == 30);

    delta_xy_free(d);
}

/* 3. set_create gives an empty set */
static void test_set_create_empty(void) {
    TEST("math_structure_blueprint_set_create — empty");

    math_structure_blueprint_set_t* msbs = math_structure_blueprint_set_create();
    EXPECT(msbs != NULL);
    EXPECT(msbs->msb_i    == 0);
    EXPECT(msbs->msb_size == 0);
    EXPECT(msbs->msb_arr  == NULL);

    free(msbs);   /* nothing else allocated yet */
}

/* 4. set_append — single item */
static void test_set_append_single(void) {
    TEST("math_structure_blueprint_set_append — single item");

    math_structure_blueprint_set_t* msbs = math_structure_blueprint_set_create();
    math_structure_blueprint_set_append(
        msbs,
        "Test Item", "\\test", "T",
        MP_DEFAULT_START_WIDTH, MP_DEFAULT_START_HEIGHT,
        NULL, NULL, SINGLE_CHARACTER
    );

    EXPECT(msbs->msb_i       == 1);
    EXPECT(msbs->msb_arr     != NULL);
    EXPECT(strcmp(msbs->msb_arr[0].name,      "Test Item") == 0);
    EXPECT(strcmp(msbs->msb_arr[0].code,      "\\test")    == 0);
    EXPECT(strcmp(msbs->msb_arr[0].character, "T")         == 0);
    EXPECT(msbs->msb_arr[0].item_delta_set == NULL);
    EXPECT(msbs->msb_arr[0].special        == SINGLE_CHARACTER);

    math_structure_blueprint_set_free(msbs);
}

/* 5. set_append — many items (forces realloc) */
static void test_set_append_many(void) {
    TEST("math_structure_blueprint_set_append — many items (realloc path)");

    math_structure_blueprint_set_t* msbs = math_structure_blueprint_set_create();

    char name[32], code[32];
    for (int i = 0; i < 20; i++) {
        sprintf(name, "Item%d", i);
        sprintf(code, "\\item%d", i);
        math_structure_blueprint_set_append(
            msbs, name, code, "x",
            MP_DEFAULT_START_WIDTH, MP_DEFAULT_START_HEIGHT,
            NULL, NULL, SINGLE_CHARACTER
        );
    }

    EXPECT(msbs->msb_i == 20);

    /* spot-check first and last */
    EXPECT(strncmp(msbs->msb_arr[0].name,  "Item0",  5)  == 0);
    EXPECT(strncmp(msbs->msb_arr[19].name, "Item19", 6)  == 0);

    math_structure_blueprint_set_free(msbs);
}

/* 6. cf_alphabetic_singular */
static void test_cf_alphabetic_singular(void) {
    TEST("cf_alphabetic_singular");

    EXPECT(cf_alphabetic_singular("a")  == 1);
    EXPECT(cf_alphabetic_singular("Z")  == 1);
    EXPECT(cf_alphabetic_singular("m")  == 1);

    EXPECT(cf_alphabetic_singular("ab") == 0);   /* two letters */
    EXPECT(cf_alphabetic_singular("1")  == 0);   /* digit */
    EXPECT(cf_alphabetic_singular("\\") == 0);   /* backslash */
    EXPECT(cf_alphabetic_singular("")   == 0);   /* empty */
}

/* 7. Full defining set — structure checks */
static void test_defining_set_structure(void) {
    TEST("math_structure_blueprint_set_defining — structure");

    math_structure_blueprint_set_t* msbs = math_structure_blueprint_set_defining();
    EXPECT(msbs != NULL);
    /* There are 13 blueprints defined in the .c file */
    EXPECT(msbs->msb_i == 13);

    math_structure_blueprint_set_free(msbs);
}

/* 8. Integral blueprint has 4 child positions */
static void test_integral_has_four_children(void) {
    TEST("integral blueprint — 4 child delta positions");

    math_structure_blueprint_set_t* msbs = math_structure_blueprint_set_defining();

    /* Find the integral entry by code */
    math_structure_blueprint_t* integral = NULL;
    for (int i = 0; i < msbs->msb_i; i++) {
        if (strcmp(msbs->msb_arr[i].code, "\\int") == 0) {
            integral = &msbs->msb_arr[i];
            break;
        }
    }

    EXPECT(integral != NULL);
    if (integral) {
        EXPECT(integral->item_delta_set         != NULL);
        EXPECT(integral->item_delta_set->length == 4);
    }

    math_structure_blueprint_set_free(msbs);
}

/* 9. Exponent blueprint has 2 child positions */
static void test_exponent_has_two_children(void) {
    TEST("exponent blueprint — 2 child delta positions");

    math_structure_blueprint_set_t* msbs = math_structure_blueprint_set_defining();

    math_structure_blueprint_t* exp_bp = NULL;
    for (int i = 0; i < msbs->msb_i; i++) {
        if (strcmp(msbs->msb_arr[i].code, "\\exp") == 0) {
            exp_bp = &msbs->msb_arr[i];
            break;
        }
    }

    EXPECT(exp_bp != NULL);
    if (exp_bp) {
        EXPECT(exp_bp->item_delta_set         != NULL);
        EXPECT(exp_bp->item_delta_set->length == 2);
        /* second child should be offset upward (negative dy) */
        EXPECT(exp_bp->item_delta_set->dy[1]  < 0);
    }

    math_structure_blueprint_set_free(msbs);
}

/* 10. Variable blueprint uses the alphabetic check function */
static void test_variable_check_func(void) {
    TEST("variable blueprint — check_func is cf_alphabetic_singular");

    math_structure_blueprint_set_t* msbs = math_structure_blueprint_set_defining();

    math_structure_blueprint_t* var = NULL;
    for (int i = 0; i < msbs->msb_i; i++) {
        if (strcmp(msbs->msb_arr[i].code, "\\variable") == 0) {
            var = &msbs->msb_arr[i];
            break;
        }
    }

    EXPECT(var != NULL);
    if (var) {
        EXPECT(var->check_func != NULL);
        /* exercise it through the stored pointer */
        EXPECT(var->check_func("x") == 1);
        EXPECT(var->check_func("3") == 0);
    }

    math_structure_blueprint_set_free(msbs);
}

/* 11. Blueprints with NULL delta have no children */
static void test_no_delta_entries(void) {
    TEST("blueprints with NULL delta — sin, cos, Close Bracket, Variable");

    math_structure_blueprint_set_t* msbs = math_structure_blueprint_set_defining();

    /* Close Bracket and Variable are defined with NULL delta */
    const char* null_delta_codes[] = { ")", "\\variable" };
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < msbs->msb_i; i++) {
            if (strcmp(msbs->msb_arr[i].code, null_delta_codes[k]) == 0) {
                EXPECT(msbs->msb_arr[i].item_delta_set == NULL);
                break;
            }
        }
    }

    math_structure_blueprint_set_free(msbs);
}

/* 12. set_append — strings are copies (safe_strdup) */
static void test_strings_are_copies(void) {
    TEST("set_append — stored strings are independent copies");

    math_structure_blueprint_set_t* msbs = math_structure_blueprint_set_create();

    char name[32] = "Original";
    char code[32] = "\\orig";
    math_structure_blueprint_set_append(
        msbs, name, code, "O",
        MP_DEFAULT_START_WIDTH, MP_DEFAULT_START_HEIGHT,
        NULL, NULL, SINGLE_CHARACTER
    );

    /* Mutate the source buffers */
    strcpy(name, "XXXXXXXX");
    strcpy(code, "\\XXXXXXX");

    /* Stored copies must be unaffected */
    EXPECT(strcmp(msbs->msb_arr[0].name, "Original") == 0);
    EXPECT(strcmp(msbs->msb_arr[0].code, "\\orig")   == 0);

    math_structure_blueprint_set_free(msbs);
}

/* ── main ──────────────────────────────────────────────────────────────── */

int main(void) {
    printf("=== Math Structure Blueprint Tests ===\n");

    test_delta_xy_create_first();
    test_delta_xy_append();
    test_set_create_empty();
    test_set_append_single();
    test_set_append_many();
    test_cf_alphabetic_singular();
    test_defining_set_structure();
    test_integral_has_four_children();
    test_exponent_has_two_children();
    test_variable_check_func();
    test_no_delta_entries();
    test_strings_are_copies();

    printf("\n=== Results: %d / %d passed ===\n", tests_passed, tests_run);
    return (tests_passed == tests_run) ? 0 : 1;
}
