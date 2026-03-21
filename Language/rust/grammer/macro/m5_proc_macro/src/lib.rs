//! # M5: 过程宏进阶
//!
//! 本模块演示 function-like 宏和 attribute 宏。
//!
//! 过程宏有三种类型：
//! 1. **Derive 宏** - `#[derive(MyTrait)]` - M4已学习
//! 2. **Function-like 宏** - `my_macro!(args)` - 类似函数调用
//! 3. **Attribute 宏** - `#[my_macro]` 或 `#[my_macro(args)]` - 附加到项上

extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, DeriveInput, ItemFn, parse::Parse, parse::ParseStream, Expr, Token, Ident, LitStr};

// ============================================================================
// Day 1: function-like 过程宏
// ============================================================================

/// function-like 宏看起来像函数调用：`my_macro!(args)`
///
/// 与 derive 不同，它们可以接受任意参数，不依赖类型。
///
/// 使用 `#[proc_macro]` 属性定义。

/// 简单的字符串处理宏：将输入转换为大写
///
/// # 示例
/// ```ignore
/// use m5_proc_macro::uppercase;
/// let result = uppercase!(hello world);
/// // 展开为："HELLO WORLD"
/// ```
#[proc_macro]
pub fn uppercase(input: TokenStream) -> TokenStream {
    let input_str = input.to_string();
    let uppercase_str = input_str.to_uppercase();

    let output = quote! {
        #uppercase_str
    };

    TokenStream::from(output)
}

/// 简单的 SQL DSL 宏示例
///
/// 这是一个非常简化的实现，演示如何处理 DSL 输入。
/// 实际项目中可能需要完整的 SQL 解析器。
///
/// # 示例
/// ```ignore
/// use m5_proc_macro::sql;
/// let query = sql!(SELECT * FROM users WHERE id = 42);
/// // 返回字符串: "Executing SQL: SELECT * FROM users WHERE id = 42"
/// ```
#[proc_macro]
pub fn sql(input: TokenStream) -> TokenStream {
    let sql_str = input.to_string();

    // 生成返回格式化字符串的代码
    let output = quote! {
        format!("Executing SQL: {}", #sql_str)
    };

    TokenStream::from(output)
}

/// 计算宏：在编译期执行简单的数学表达式
///
/// # 示例
/// ```ignore
/// use m5_proc_macro::compute;
/// let result = compute!(1 + 2 * 3);
/// // 这只是一个演示，实际并不执行计算
/// ```
#[proc_macro]
pub fn compute(input: TokenStream) -> TokenStream {
    // 这里我们只是返回表达式本身
    // 实际项目可以使用 const eval 或其他技术
    let expr: Expr = parse_macro_input!(input as Expr);

    let output = quote! {
        (#expr)
    };

    TokenStream::from(output)
}

// ============================================================================
// Day 2: attribute 过程宏
// ============================================================================

/// attribute 宏附加到函数、结构体等项上：`#[my_macro]`
///
/// 它们可以修改、替换或增强被附加的项。
///
/// 使用 `#[proc_macro_attribute]` 属性定义。
/// 参数：`_attr` - 属性参数，`item` - 被附加的项

/// 路由属性宏示例 - 模拟 Web 框架中的路由定义
///
/// 将函数包装为路由处理器，添加进入日志。
///
/// # 示例
/// ```ignore
/// use m5_proc_macro::route;
/// #[route]
/// fn home() {
///     println!("Home page");
/// }
///
/// // 调用 home() 会输出:
/// // "[ROUTE] Executing handler: home"
/// // "Home page"
/// ```
#[proc_macro_attribute]
pub fn route(_attr: TokenStream, item: TokenStream) -> TokenStream {
    let input = parse_macro_input!(item as ItemFn);

    let fn_name = &input.sig.ident;
    let fn_vis = &input.vis;
    let fn_sig = &input.sig;
    let fn_block = &input.block;

    // 生成新的函数，添加进入日志
    let expanded = quote! {
        #fn_vis #fn_sig {
            println!("[ROUTE] Executing handler: {}", stringify!(#fn_name));
            #fn_block
        }
    };

    TokenStream::from(expanded)
}

/// 调试打印属性宏 - 自动打印函数进入和退出信息
///
/// # 示例
/// ```ignore
/// use m5_proc_macro::debug_print;
/// #[debug_print]
/// fn my_function() {
///     println!("Doing work...");
/// }
///
/// // 调用 my_function() 会输出:
/// // ">>> Entering my_function"
/// // "Doing work..."
/// // "<<< Exiting my_function"
/// ```
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
            let __result = #fn_block;
            println!("<<< Exiting {}", stringify!(#fn_name));
            __result
        }
    };

    TokenStream::from(expanded)
}

// ============================================================================
// Day 3: 自定义语法解析 - syn 深入
// ============================================================================

/// 自定义解析结构 - 用于解析属性参数
///
/// 示例：`#[log_call(level = "debug", message = "custom")]`
struct LogCallArgs {
    level: String,
    message: Option<String>,
}

impl Parse for LogCallArgs {
    fn parse(input: ParseStream) -> syn::Result<Self> {
        let mut level = "info".to_string(); // 默认值
        let mut message = None;

        // 解析类似: level = "debug", message = "custom"
        while !input.is_empty() {
            let key: Ident = input.parse()?;
            let _: Token![=] = input.parse()?;

            if key == "level" {
                let val: LitStr = input.parse()?;
                level = val.value();
            } else if key == "message" {
                let val: LitStr = input.parse()?;
                message = Some(val.value());
            }

            // 处理可选的逗号
            if input.peek(Token![,]) {
                let _: Token![,] = input.parse()?;
            }
        }

        Ok(LogCallArgs { level, message })
    }
}

/// 带参数的日志记录宏
///
/// 支持：`#[log_call]` 或 `#[log_call(level = "debug")]` 或 `#[log_call(level = "info", message = "custom")]`
///
/// # 示例
/// ```ignore
/// use m5_proc_macro::log_call;
/// #[log_call]
/// fn function_a() {
///     println!("Work A");
/// }
///
/// #[log_call(level = "debug")]
/// fn function_b() {
///     println!("Work B");
/// }
///
/// // 调用会输出带级别前缀的日志
/// ```
#[proc_macro_attribute]
pub fn log_call(attr: TokenStream, item: TokenStream) -> TokenStream {
    // 解析属性参数
    let args = if attr.is_empty() {
        LogCallArgs {
            level: "info".to_string(),
            message: None,
        }
    } else {
        match syn::parse::<LogCallArgs>(attr) {
            Ok(args) => args,
            Err(e) => return e.to_compile_error().into(),
        }
    };

    let input = parse_macro_input!(item as ItemFn);
    let fn_name = &input.sig.ident;
    let fn_vis = &input.vis;
    let fn_sig = &input.sig;
    let fn_block = &input.block;

    let level = args.level;
    let msg_prefix = args.message.unwrap_or_else(|| fn_name.to_string());

    let expanded = quote! {
        #fn_vis #fn_sig {
            println!("[{}] Calling: {}", #level, #msg_prefix);
            let __result = #fn_block;
            println!("[{}] Finished: {}", #level, #msg_prefix);
            __result
        }
    };

    TokenStream::from(expanded)
}

/// 测量执行时间的属性宏
///
/// # 示例
/// ```ignore
/// use m5_proc_macro::timed;
/// #[timed]
/// fn slow_function() {
///     std::thread::sleep(std::time::Duration::from_millis(10));
/// }
///
/// // 调用会输出:
/// // "[TIMED] slow_function took Xms"
/// ```
#[proc_macro_attribute]
pub fn timed(_attr: TokenStream, item: TokenStream) -> TokenStream {
    let input = parse_macro_input!(item as ItemFn);

    let fn_name = &input.sig.ident;
    let fn_vis = &input.vis;
    let fn_sig = &input.sig;
    let fn_block = &input.block;

    let expanded = quote! {
        #fn_vis #fn_sig {
            let __start = std::time::Instant::now();
            let __result = #fn_block;
            let __elapsed = __start.elapsed();
            println!("[TIMED] {} took {:?}", stringify!(#fn_name), __elapsed);
            __result
        }
    };

    TokenStream::from(expanded)
}

// ============================================================================
// Day 4: 综合练习 - 自定义 derive + attribute 组合
// ============================================================================

/// 自定义 derive 宏 - 为结构体实现 Default 的变体
///
/// 与标准 #[derive(Default)] 不同，这个宏可以为字段指定自定义默认值
///
/// # 示例
/// ```ignore
/// use m5_proc_macro::CustomDefault;
/// #[derive(CustomDefault)]
/// struct Config {
///     #[default = "localhost"]
///     host: String,
///     #[default = 8080]
///     port: u16,
/// }
/// ```
#[proc_macro_derive(CustomDefault)]
pub fn custom_default_derive(input: TokenStream) -> TokenStream {
    let input = parse_macro_input!(input as DeriveInput);
    let name = &input.ident;

    let expanded = quote! {
        impl Default for #name {
            fn default() -> Self {
                Self {
                    // 简化实现：实际应该解析属性
                    ..Default::default()
                }
            }
        }
    };

    TokenStream::from(expanded)
}

/// 重复执行属性宏
///
/// 格式：`#[repeat(n = 3)]` - 将函数体执行 n 次
///
/// # 示例
/// ```ignore
/// use m5_proc_macro::repeat;
/// #[repeat(n = 3)]
/// fn do_something() {
///     println!("Hello");
/// }
///
/// // 调用 do_something() 会输出 "Hello" 3 次
/// ```
struct RepeatArgs {
    n: usize,
}

impl Parse for RepeatArgs {
    fn parse(input: ParseStream) -> syn::Result<Self> {
        let key: Ident = input.parse()?;
        if key != "n" {
            return Err(syn::Error::new(key.span(), "expected `n`"));
        }
        let _: Token![=] = input.parse()?;
        let n: syn::LitInt = input.parse()?;
        let n = n.base10_parse()?;
        Ok(RepeatArgs { n })
    }
}

#[proc_macro_attribute]
pub fn repeat(attr: TokenStream, item: TokenStream) -> TokenStream {
    let args = match syn::parse::<RepeatArgs>(attr) {
        Ok(args) => args,
        Err(e) => return e.to_compile_error().into(),
    };

    let input = parse_macro_input!(item as ItemFn);

    let _fn_name = &input.sig.ident;
    let fn_vis = &input.vis;
    let fn_sig = &input.sig;
    let fn_block = &input.block;
    let n = args.n;

    // 生成重复执行 n 次的代码
    let mut stmts = Vec::new();
    for _ in 0..n {
        stmts.push(quote! { #fn_block });
    }

    let expanded = quote! {
        #fn_vis #fn_sig {
            #(#stmts)*
        }
    };

    TokenStream::from(expanded)
}
