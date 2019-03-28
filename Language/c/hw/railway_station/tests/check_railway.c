/*
 * File Name: check_railway.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 22 Mar 2019 02:15:31 PM CST
 */

#include "railway.h"
#include "check.h"
#include <stdlib.h>


START_TEST(test_1) {
    // "test_1 fail" 失败错误信息
    fail_unless(JudgeTrainSequence(5, "12345") == 1, "test_1 fail");
}
END_TEST

START_TEST(test_2) {
    fail_unless(JudgeTrainSequence(5, "21345") == 1, "test_2 fail");
}
END_TEST

START_TEST(test_3) {
    fail_unless(JudgeTrainSequence(5, "53241") == 0, "test_3 fail");
}
END_TEST

START_TEST(test_4) {
    fail_unless(JudgeTrainSequence(1, "1") == 1, "test_4 fail");
}
END_TEST

START_TEST(test_5) {
    fail_unless(JudgeTrainSequence(9, "123456789") == 1, "test_5 fail");
}
END_TEST

START_TEST(test_6) {
    fail_unless(JudgeTrainSequence(9, "123567894") == 1, "test_6 fail");
}
END_TEST

START_TEST(test_7) {
    fail_unless(JudgeTrainSequence(9, "123678945") == 0, "test_7 fail");
}
END_TEST

// maxNum小于1
START_TEST(test_8) {
    fail_unless(JudgeTrainSequence(0, "") == 0, "test maxNum<1 fail");
}
END_TEST

// maxNum大于9
START_TEST(test_9) {
    fail_unless(JudgeTrainSequence(10, "1234567890") == 0, "test maxNum>9 fail");
}
END_TEST

// pOutSeq长度大于maxNum输入
START_TEST(test_10) {
    fail_unless(JudgeTrainSequence(3, "1234") == 0, "test len(pOutSeq)>maxNum fail");
}
END_TEST

// pOutSeq长度小于maxNum输入
START_TEST(test_11) {
    fail_unless(JudgeTrainSequence(3, "12") == 0, "test len(pOutSeq)<maxNum fail");
}
END_TEST

// pOutSeq含有非法字符
START_TEST(test_12) {
    fail_unless(JudgeTrainSequence(3, "12$") == 0, "test len(pOutSeq)<maxNum fail");
}
END_TEST

// pOutSeq含有不在maxNum范围内的数字
START_TEST(test_13) {
    fail_unless(JudgeTrainSequence(3, "124") == 0, "test len(pOutSeq)<maxNum fail");
}
END_TEST


Suite * make_railway_suite(void) {
    // 建立Suite
    Suite *s = suite_create("railway");
    // 建立测试用例集
    TCase *tc_railway = tcase_create("railway");
    // 将测试用例加到Suite中
    suite_add_tcase(s, tc_railway);
    // 测试用例加到测试集中
    tcase_add_test(tc_railway, test_1);
    tcase_add_test(tc_railway, test_2);
    tcase_add_test(tc_railway, test_3);
    tcase_add_test(tc_railway, test_4);
    tcase_add_test(tc_railway, test_5);
    tcase_add_test(tc_railway, test_6);
    tcase_add_test(tc_railway, test_7);
    tcase_add_test(tc_railway, test_8);
    tcase_add_test(tc_railway, test_9);
    tcase_add_test(tc_railway, test_10);
    tcase_add_test(tc_railway, test_11);
    tcase_add_test(tc_railway, test_12);
    tcase_add_test(tc_railway, test_13);

    return s;
}

int main(void) {
    int n;
    SRunner *sr;

    // 将Suite加入到SRunner
    sr = srunner_create(make_railway_suite());
    srunner_run_all(sr, CK_NORMAL);
    // 运行所有测试用例
    n = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (n == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
