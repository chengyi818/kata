//! 练习：实现一个 AST 构建宏
//!
//! 目标：实现一个可以构建抽象语法树（AST）的宏
//!
//! 假设我们有一个简单的表达式 AST：
//! ```rust
//! enum Expr {
//!     Literal(i32),
//!     Add(Box<Expr>, Box<Expr>),
//!     Mul(Box<Expr>, Box<Expr>),
//! }
//! ```
//!
//! 我们希望可以用这样的语法构建 AST：
//! ```rust
//! ast!(1 + 2 * 3)
//! ```
//!
//! 提示：
//! 1. 这需要递归宏来解析嵌套表达式
//! 2. 需要考虑运算符优先级
//! 3. 可以使用 TT Muncher 模式
//!
//! 练习步骤：
//! 1. 先定义 Expr 枚举
//! 2. 实现 ast! 宏支持字面量
//! 3. 添加对 + 和 * 的支持
//! 4. 实现一个简单的求值函数

// TODO: 定义 Expr 枚举
/*
#[derive(Debug, PartialEq)]
enum Expr {
    Literal(i32),
    Add(Box<Expr>, Box<Expr>),
    Mul(Box<Expr>, Box<Expr>),
}

impl Expr {
    fn eval(&self) -> i32 {
        match self {
            Expr::Literal(n) => *n,
            Expr::Add(left, right) => left.eval() + right.eval(),
            Expr::Mul(left, right) => left.eval() * right.eval(),
        }
    }
}
*/

// TODO: 实现 ast! 宏

// 测试模板
#[cfg(test)]
mod tests {
    use super::*;

    // TODO: 当你实现宏后，取消注释这些测试

    /*
    #[test]
    fn test_ast_literal() {
        let expr = ast!(42);
        assert_eq!(expr, Expr::Literal(42));
        assert_eq!(expr.eval(), 42);
    }

    #[test]
    fn test_ast_addition() {
        let expr = ast!(1 + 2);
        assert_eq!(expr.eval(), 3);
    }

    #[test]
    fn test_ast_multiplication() {
        let expr = ast!(2 * 3);
        assert_eq!(expr.eval(), 6);
    }

    #[test]
    fn test_ast_mixed() {
        let expr = ast!(1 + 2 * 3);
        // 注意：简单的实现可能不处理优先级
        // 你的实现应该能正确计算
        assert_eq!(expr.eval(), 7);
    }
    */
}
