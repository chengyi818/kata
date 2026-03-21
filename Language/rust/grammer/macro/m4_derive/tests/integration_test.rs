//! M4 过程宏集成测试
//!
//! 测试 Hello, Describe, Builder 三个 derive 宏

use m4_derive::{Hello, Describe, Builder};

// ============================================================================
// Trait 定义（使用者在代码中定义）
// ============================================================================

pub trait Hello {
    fn hello(&self);
}

pub trait Describe {
    fn describe(&self) -> String;
}

// ============================================================================
// 测试 Hello derive
// ============================================================================

#[derive(Hello)]
struct Person {
    name: String,
    age: u32,
}

#[test]
fn test_hello_derive() {
    let p = Person {
        name: "Alice".to_string(),
        age: 30,
    };
    // 由于 hello() 打印到 stdout，我们主要验证它能编译和运行
    p.hello();  // 输出: Hello, I am Person!
}

// ============================================================================
// 测试 Describe derive
// ============================================================================

#[derive(Describe, Debug)]
struct Point {
    x: i32,
    y: i32,
}

#[test]
fn test_describe_derive() {
    let p = Point { x: 10, y: 20 };
    let desc = p.describe();
    assert!(desc.contains("Point"));
    assert!(desc.contains("x:"));
    assert!(desc.contains("10"));
    assert!(desc.contains("y:"));
    assert!(desc.contains("20"));
}

#[derive(Describe, Debug)]
struct Config {
    host: String,
    port: u16,
    debug: bool,
}

#[test]
fn test_describe_derive_complex() {
    let config = Config {
        host: "localhost".to_string(),
        port: 8080,
        debug: true,
    };
    let desc = config.describe();
    assert!(desc.contains("Config"));
    assert!(desc.contains("host:"));
    assert!(desc.contains("port:"));
    assert!(desc.contains("debug:"));
}

// ============================================================================
// 测试 Builder derive
// ============================================================================

#[derive(Builder, Debug)]
struct ServerConfig {
    host: String,
    port: u16,
}

#[test]
fn test_builder_derive_success() {
    let config = ServerConfig::builder()
        .host("localhost".to_string())
        .port(8080)
        .build()
        .unwrap();

    assert_eq!(config.host, "localhost");
    assert_eq!(config.port, 8080);
}

#[test]
fn test_builder_derive_missing_field() {
    let result = ServerConfig::builder()
        .host("localhost".to_string())
        // 没有设置 port
        .build();

    assert!(result.is_err());
    assert!(result.unwrap_err().contains("port"));
}

#[derive(Builder, Debug)]
struct DatabaseConfig {
    url: String,
    username: String,
    password: String,
    pool_size: u32,
}

#[test]
fn test_builder_derive_multiple_fields() {
    let config = DatabaseConfig::builder()
        .url("postgres://localhost/mydb".to_string())
        .username("admin".to_string())
        .password("secret".to_string())
        .pool_size(10)
        .build()
        .unwrap();

    assert_eq!(config.url, "postgres://localhost/mydb");
    assert_eq!(config.username, "admin");
    assert_eq!(config.password, "secret");
    assert_eq!(config.pool_size, 10);
}

#[test]
fn test_builder_derive_chaining() {
    let builder = ServerConfig::builder()
        .host("127.0.0.1".to_string());

    // 测试链式调用可以继续
    let config = builder
        .port(3000)
        .build()
        .unwrap();

    assert_eq!(config.host, "127.0.0.1");
    assert_eq!(config.port, 3000);
}
