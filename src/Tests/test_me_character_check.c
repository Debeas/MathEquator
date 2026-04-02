#include "..\me_character_check.h"


/* -------------------------------------------------------------------------- */

static int tests_run = 0;
static int tests_passed = 0;

// Copied Claude's code
#define TEST(name) \
do { printf("\n[TEST] %s\n", name); } while(0)

#define TEST_FINISH(name) \
do { printf("\n[TEST FINISH] %s\n", name); } while(0)

#define EXPECT(cond) \
do { \
    tests_run++; \
    if (cond) { \
        printf("  PASS: %s\n", #cond); \
        tests_passed++; \
    } else { \
        printf("  FAIL: %s  (line %d)\n", #cond, __LINE__); \
    } \
} while(0)

/* -------------------------------------------------------------------------- */

void test_character_check_set_create();
void test_character_check_set_alphabetic();

int main() {
    test_character_check_set_alphabetic();  
}

void test_character_check_set_create() {
    TEST("Create and Free character check set");
    character_check_set_t* ccs = character_check_set_create();
    character_check_set_free(ccs);
    
    TEST_FINISH("Create and Free character check set");
}

void test_character_check_set_alphabetic() {
    TEST("Create and Free character check set");
    character_check_set_t* ccs = character_check_set_create();
    character_check_set_free(ccs);
    
    character_check_set_set(ccs, ALPHABETIC, 8);
    int value = 0;
    EXPECT((value = character_check_set_parse(ccs, "worth")) == 8);
    printf("%d\n",value);
    TEST_FINISH("Create and Free character check set");
}