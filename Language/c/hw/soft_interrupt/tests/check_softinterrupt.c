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

void proc_add_1() {
    proc_ret += 1;
    return;
}

void proc_3_add_1() {
    SwiActivate(5);
    SwiActivate(5);
    SwiActivate(5);
    Clear();
}

void setup(void) {
    proc_ret = 1;

    SwiCreate(5, 10, proc_add_1);
    SwiCreate(6, 10, proc_3_add_1);
}

void teardown(void) {
}

START_TEST(test_SwiCreate_0) {
    int ret;

    ret = SwiCreate(0, 0, proc_add_1);
    fail_unless(ret == 0, "注册swiId 0失败");
}
END_TEST

START_TEST(test_SwiCreate_1) {
    int ret;

    ret = SwiCreate(100, 10, proc_add_1);
    fail_unless(ret == -1, "注册非法swiId, 测试失败");
}
END_TEST

START_TEST(test_SwiCreate_2) {
    int ret;

    ret = SwiCreate(10, 33, proc_add_1);
    fail_unless(ret == -1, "注册非法prio, 测试失败");
}
END_TEST

START_TEST(test_SwiCreate_3) {
    int ret;

    ret = SwiCreate(20, 31, NULL);
    fail_unless(ret == -1, "注册proc为空, 测试失败");
}
END_TEST

START_TEST(test_SwiCreate_4) {
    int ret;

    ret = SwiCreate(22, 22, proc_add_1);
    fail_unless(ret == 0, "注册swiId22, 测试失败");
    ret = SwiCreate(22, 22, proc_add_1);
    fail_unless(ret == -1, "重复注册swiId22, 测试失败");
}
END_TEST

START_TEST(test_SwiActivate_0) {
    int ret;

    ret = SwiActivate(5);
    fail_unless(ret == 0, "运行swiId 5失败");
    fail_unless(proc_ret == 2, "swiId执行失败");

    ret = SwiActivate(1);
    fail_unless(ret == -1, "执行未注册进程,测试失败");
}
END_TEST

START_TEST(test_SwiClear_0) {
    int ret;

    ret = SwiActivate(6);
    fail_unless(ret == 0, "运行swiId 6失败");
    fail_unless(proc_ret == 1, "swiId 6执行失败");
    ret = SwiActivate(6);
    fail_unless(ret == -1, "运行swiId 6 after Clear,测试失败");
}
END_TEST



Suite* softinterrupt_suite(void)
{
    Suite* s = suite_create("softinterrupt");

    /* test SwiCreate */
    TCase* tc_create = tcase_create("SwiCreate");
    tcase_add_test(tc_create, test_SwiCreate_0);
    tcase_add_test(tc_create, test_SwiCreate_1);
    tcase_add_test(tc_create, test_SwiCreate_2);
    tcase_add_test(tc_create, test_SwiCreate_3);
    tcase_add_test(tc_create, test_SwiCreate_4);
    suite_add_tcase(s, tc_create);

    /* test SwiActivate */
    TCase* tc_activate = tcase_create("SwiActivate");
    tcase_add_checked_fixture(tc_activate, setup, teardown);
    tcase_add_test(tc_activate, test_SwiActivate_0);
    suite_add_tcase(s, tc_activate);

    /* test Clear */
    TCase* tc_clear = tcase_create("Clear");
    tcase_add_checked_fixture(tc_clear, setup, teardown);
    tcase_add_test(tc_clear, test_SwiClear_0);
    suite_add_tcase(s, tc_clear);

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
