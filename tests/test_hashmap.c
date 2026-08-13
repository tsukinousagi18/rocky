// Compile : 
// cl / nologo / I include / I external / unity / src tests\test_hashmap.c src\hashmap.c external / unity / src / unity.c / link / OUT:test_hashmap.exe
// run : .\test_hashmap.exe

#include "unity.h"
#include "rocky/adt/hashmap.h"

void setUp(void) {}
void tearDown(void) {}

void test_set_get_replace_delete(void)
{
    HashMap* m = create_hashmap(4);
    TEST_ASSERT_NOT_NULL(m);

    const char* k = "key";
    int v = 123;
    hashmap_set(m, k, &v);

    TEST_ASSERT_TRUE(hashmap_contains(m, k));
    TEST_ASSERT_EQUAL_INT(123, *(int*)hashmap_get(m, k));

    int v2 = 999;
    hashmap_set(m, k, &v2);
    TEST_ASSERT_EQUAL_INT(999, *(int*)hashmap_get(m, k));

    void* deleted = hashmap_delete(m, k);
    TEST_ASSERT_NOT_NULL(deleted);
    TEST_ASSERT_FALSE(hashmap_contains(m, k));

    free_hashmap(m);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_set_get_replace_delete);
    return UNITY_END();
}