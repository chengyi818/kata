//! # M5: 过程宏进阶
//!
//! 本模块演示 function-like 宏和 attribute 宏。
//!
//! 宏 2.0 统一 TokenStream 流水线让所有过程宏类型协同工作：
//! 1. Token 收集：调用处被解析为 TokenStream
//! 2. 宏匹配/执行：声明式宏或过程宏处理并返回新的 TokenStream
//! 3. 重新解析：编译器继续解析生成的代码
//! 4. 工具链协同：rust-analyzer、Clippy 都能处理展开后的代码
//!
//! **注意**：过程宏 crate 不能在同 crate 中使用自己的宏。
//! 测试应在单独的 integration test crate 中进行。

extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, ItemFn, parse::Parser};

// ============================================================================
// Day 1: function-like 过程宏
// ============================================================================

/// function-like 宏看起来像函数调用：`my_macro!(args)`
///
/// 与 derive 不同，它们可以接受任意参数，不依赖类型。
/// 在宏 2.0 中，它们和声明宏共用相同的 TokenStream 流水线。

/// 简单的字符串处理宏
#[proc_macro]
pub fn uppercase(input: TokenStream) -> TokenStream {
    let input_str = input.to_string();
    let uppercase = input_str.to_uppercase();

    let output = quote! {
        #uppercase
    };

    TokenStream::from(output)
}

/// 简单的 DSL 宏示例：SQL 查询（非常简化）
///
/// 宏 2.0 调试技巧：使用 `cargo expand` 查看宏展开结果
#[proc_macro]
pub fn sql(input: TokenStream) -> TokenStream {
    let sql_str = input.to_string();

    let output = quote! {
        format!("Executing SQL: {}", #sql_str)
    };

    TokenStream::from(output)
}

// ============================================================================
// Day 2: attribute 过程宏
// ============================================================================

/// attribute 宏附加到函数、结构体等项上：`#[my_macro]`
///
/// 它们可以修改、替换或增强被附加的项。
/// 这是宏 2.0 TokenStream 流水线的重要应用场景。

/// 调试打印属性宏
///
/// 宏 2.0 卫生特性：生成的代码保持正确的 Span 信息，
/// 编译器错误能指向正确的位置
#[proc_macro_attribute]
pub fn debug_print(_attr: TokenStream, item: TokenStream) -> TokenStream {
    let input = parse_macro_input!(item as ItemFn);

    let fn_name = &input.sig.ident;
    let fn_vis = &input.vis;
    let fn_sig = &input.sig;
    let fn_block = &input.block;

    let expanded = quote! {
        #fn_vis #fn_sig {
            println!(">>> Entering {}", stringify!(#fn_name));
            let result = #fn_block;
            println!("<<< Exiting {}", stringify!(#fn_name));
            result
        }
    };

    TokenStream::from(expanded)
}

/// 计时属性宏
#[proc_macro_attribute]
pub fn timed(_attr: TokenStream, item: TokenStream) -> TokenStream {
    let input = parse_macro_input!(item as ItemFn);

    let fn_name = &input.sig.ident;
    let fn_vis = &input.vis;
    let fn_sig = &input.sig;
    let fn_block = &input.block;

    let expanded = quote! {
        #fn_vis #fn_sig {
            let start = ::std::time::Instant::now();
            let result = #fn_block;
            let duration = start.elapsed();
            println!("{} took {:?}", stringify!(#fn_name), duration);
            result
        }
    };

    TokenStream::from(expanded)
}

// ============================================================================
// Day 3: 自定义语法解析
// ============================================================================

/// 这个宏可以接受参数，如 `#[log_call(level = "debug")]`
///
/// 演示了如何解析属性参数，这是宏 2.0 高级特性
#[proc_macro_attribute]
pub fn log_call(attr: TokenStream, item: TokenStream) -> TokenStream {
    // 解析属性参数
    let parser = syn::punctuated::Punctuated::<syn::Meta, syn::Token![,]>::parse_terminated;
    let args = match parser.parse(attr) {
        Ok(args) => args,
        Err(e) => return e.to_compile_error().into(),
    };

    // 解析 level 参数
    let mut level = "info".to_string();
    for arg in args {
        if let syn::Meta::NameValue(nv) = arg {
            if nv.path.is_ident("level") {
                if let syn::Expr::Lit(syn::ExprLit {
                    lit: syn::Lit::Str(s),
                    ..
                }) = nv.value
                {
                    level = s.value();
                }
            }
        }
    }

    let input = parse_macro_input!(item as ItemFn);
    let fn_name = &input.sig.ident;
    let fn_vis = &input.vis;
    let fn_sig = &input.sig;
    let fn_block = &input.block;

    let expanded = quote! {
        #fn_vis #fn_sig {
            println!("[{}] Calling {}", #level, stringify!(#fn_name));
            let result = #fn_block;
            println!("[{}] Finished {}", #level, stringify!(#fn_name));
            result
        }
    };

    TokenStream::from(expanded)
}

// ============================================================================
// 使用说明
// ============================================================================

// 使用这些宏的示例（在其他 crate 中）：
//
// use m5_proc_macro::{uppercase, sql, debug_print, timed, log_call};
//
// let result = uppercase!(hello);
// let query = sql!(SELECT * FROM users);
//
// #[debug_print]
// fn test_function() -> i32 { 42 }
//
// #[timed]
// fn slow_function() {}
//
// #[log_call]
// fn info_function() {}
//
// #[log_call(level = "debug")]
// fn debug_function() {}
