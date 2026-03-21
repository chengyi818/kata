//! M5 过程宏进阶 - 集成测试
//!
//! 测试 function-like 宏和 attribute 宏的功能

use m5_proc_macro::{uppercase, sql, compute, route, debug_print, log_call, timed, repeat};

// ============================================================================
// Day 1: function-like 过程宏测试
// ============================================================================

#[test]
fn test_uppercase_macro() {
    // uppercase! 宏将输入转换为大写字符串
    let result = uppercase!(hello);
    assert_eq!(result, "HELLO");

    let result2 = uppercase!(rust macros);
    assert_eq!(result2, "RUST MACROS");
}

#[test]
fn test_sql_macro() {
    // sql! 宏生成 SQL 执行字符串
    let query = sql!(SELECT * FROM users WHERE id = 42);
    assert!(query.contains("SELECT * FROM users WHERE id = 42"));
    assert!(query.starts_with("Executing SQL:"));
}

#[test]
fn test_compute_macro() {
    // compute! 宏返回表达式本身
    let result = compute!(1 + 2 * 3);
    assert_eq!(result, 7); // 1 + 6 = 7

    let result2 = compute!(10 * 2);
    assert_eq!(result2, 20);
}

// ============================================================================
// Day 2: attribute 过程宏测试
// ============================================================================

#[route]
fn test_route_handler() {
    println!("Handler executed");
}

#[test]
fn test_route_attribute() {
    // 调用被 #[route] 修饰的函数
    // 应该输出: "[ROUTE] Executing handler: test_route_handler"
    test_route_handler();
}

#[debug_print]
fn test_debug_function() {
    println!("Inside debug function");
}

#[test]
fn test_debug_print_attribute() {
    // 调用被 #[debug_print] 修饰的函数
    // 应该输出:
    // ">>> Entering test_debug_function"
    // "Inside debug function"
    // "<<< Exiting test_debug_function"
    test_debug_function();
}

// ============================================================================
// Day 3: 自定义语法解析测试
// ============================================================================

#[log_call]
fn function_with_default_log() {
    println!("Doing default work");
}

#[log_call(level = "debug")]
fn function_with_debug_level() {
    println!("Doing debug work");
}

#[log_call(level = "warn", message = "custom message")]
fn function_with_custom_message() {
    println!("Doing custom work");
}

#[timed]
fn quick_function() {
    // 非常快的操作
    let _ = 1 + 1;
}

#[test]
fn test_log_call_default() {
    function_with_default_log();
}

#[test]
fn test_log_call_debug() {
    function_with_debug_level();
}

#[test]
fn test_log_call_custom() {
    function_with_custom_message();
}

#[test]
fn test_timed_attribute() {
    quick_function();
    // 应该输出: "[TIMED] quick_function took Xns"
}

// ============================================================================
// Day 4: 综合练习测试
// ============================================================================

// 测试 repeat 属性宏 - 函数体应该执行多次
static mut COUNTER: u32 = 0;

#[repeat(n = 3)]
fn increment_counter() {
    unsafe {
        COUNTER += 1;
    }
}

#[test]
fn test_repeat_attribute() {
    unsafe {
        COUNTER = 0;
    }

    increment_counter();

    unsafe {
        // 由于函数体执行了 3 次，COUNTER 应该是 3
        assert_eq!(COUNTER, 3);
    }
}

// 测试带有返回值和参数的函数
#[timed]
fn add_numbers(a: i32, b: i32) -> i32 {
    a + b
}

#[debug_print]
fn multiply_numbers(a: i32, b: i32) -> i32 {
    a * b
}

#[test]
fn test_timed_with_return_value() {
    let result = add_numbers(5, 3);
    assert_eq!(result, 8);
}

#[test]
fn test_debug_print_with_return_value() {
    let result = multiply_numbers(4, 7);
    assert_eq!(result, 28);
}

// 测试嵌套属性
#[route]
#[timed]
fn nested_attributes() -> &'static str {
    "result"
}

#[test]
fn test_nested_attributes() {
    let result = nested_attributes();
    assert_eq!(result, "result");
}
