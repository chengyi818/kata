/*
 * File Name: check_soft_interrupt.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Sun 24 Mar 2019 08:53:26 PM CST
 */
#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/softinterrupt.h"

static int proc_ret;

void proc1() {
    proc_ret = 1;
    return;
}

void setup(void) {
}

void teardown(void) {
    Clear();
    proc_ret = 0;
}

START_TEST(test_SwiCreate_0) {
    int ret;

    ret = SwiCreate(0, 0, proc1);
    fail_unless(ret == 0, "test 0 0 fail");
    ret = SwiActivate(0);
    fail_unless(ret == 0, "test 0 1 fail");
    fail_unless(proc_ret == 1, "test 0 0 1 fail");

    ret = SwiActivate(1);
    fail_unless(ret == -1, "test 0 2 fail");
}
END_TEST

START_TEST(test_SwiCreate_100) {
    int ret;

    ret = SwiCreate(100, 10, proc1);
    ck_assert_int_eq(ret, -1);
}
END_TEST

START_TEST(test_SwiCreate_10) {
    int ret;

    ret = SwiCreate(10, 33, proc1);
    ck_assert_int_eq(ret, -1);
}
END_TEST

START_TEST(test_SwiCreate_20) {
    int ret;

    ret = SwiCreate(20, 31, NULL);
    ck_assert_int_eq(ret, -1);
}
END_TEST

START_TEST(test_SwiCreate_22) {
    int ret;

    ret = SwiCreate(22, 22, proc1);
    ck_assert_int_eq(ret, 0);
    ret = SwiCreate(22, 22, proc1);
    ck_assert_int_eq(ret, -1);
}
END_TEST


Suite* softinterrupt_suite(void)
{
    Suite* s = suite_create("softinterrupt");

    /* SwiCreate test case */
    TCase* tc_create = tcase_create("SwiCreate");

    tcase_add_test(tc_create, test_SwiCreate_0);
    tcase_add_test(tc_create, test_SwiCreate_10);
    tcase_add_test(tc_create, test_SwiCreate_20);
    tcase_add_test(tc_create, test_SwiCreate_22);
    tcase_add_test(tc_create, test_SwiCreate_100);

    suite_add_tcase(s, tc_create);

    TCase* tc_activate = tcase_create("SwiActivate");
    tcase_add_checked_fixture(tc_create, setup, teardown);
    suite_add_tcase(s, tc_activate);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = softinterrupt_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
