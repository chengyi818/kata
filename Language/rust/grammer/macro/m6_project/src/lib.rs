//! # M6: 综合实战
//!
//! 这个模块提供了实战项目的框架。
//!
//! 实战项目选题：
//! 1. 简化 CRUD 操作的宏
//! 2. 自动序列化宏
//! 3. 命令行解析宏
//!
//! 在这个模块中，从零设计并实现一个完整的宏库。
//!
//! 宏 2.0 工程化最佳实践：
//! - 使用模块化组织宏（`mod macros; pub use macros::*;`）
//! - 使用绝对路径（`::std::`、`::serde::`）确保宏在任何上下文中工作
//! - 提供完善的文档和示例
//! - 使用 `cargo expand` 调试宏展开
//!
//! **注意**：过程宏 crate 不能在同 crate 中使用自己的宏。
//! 测试应在单独的 integration test crate 中进行。

extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, DeriveInput, Data, Fields};

// ============================================================================
// 实战项目 1：自动实现 Display trait
// ============================================================================

/// 自动为结构体实现 Display trait
///
/// 使用方法：
/// ```rust,ignore
/// #[derive(AutoDisplay)]
/// struct Person {
///     name: String,
///     age: u32,
/// }
/// ```
/// 会生成类似 "Person { name: Alice, age: 30 }" 的显示格式
///
/// 宏 2.0 提示：生成的代码走统一 TokenStream 流水线，IDE 可以正确识别
#[proc_macro_derive(AutoDisplay)]
pub fn auto_display_derive(input: TokenStream) -> TokenStream {
    let input = parse_macro_input!(input as DeriveInput);
    let name = &input.ident;

    // 获取字段信息
    let fields = match &input.data {
        Data::Struct(data) => match &data.fields {
            Fields::Named(fields) => &fields.named,
            _ => {
                return syn::Error::new_spanned(name, "AutoDisplay requires named fields")
                    .to_compile_error()
                    .into();
            }
        },
        _ => {
            return syn::Error::new_spanned(name, "AutoDisplay only works on structs")
                .to_compile_error()
                .into();
        }
    };

    // 生成字段显示代码
    let field_displays = fields.iter().map(|f| {
        let ident = &f.ident;
        quote! {
            write!(f, "{}: {:?}, ", stringify!(#ident), self.#ident)?;
        }
    });

    let expanded = quote! {
        impl ::std::fmt::Display for #name {
            fn fmt(&self, f: &mut ::std::fmt::Formatter<'_>) -> ::std::fmt::Result {
                write!(f, "{} {{ ", stringify!(#name))?;
                #(#field_displays)*
                write!(f, "}}")
            }
        }
    };

    TokenStream::from(expanded)
}

// ============================================================================
// 实战项目 2：简化 CRUD 操作的宏
// ============================================================================

/// 这个实战项目实现了一个简化的 CRUD derive 宏
///
/// 使用方法：
/// ```rust,ignore
/// #[derive(CRUD)]
/// struct User {
///     id: u32,
///     name: String,
/// }
/// ```
///
/// 会生成：
/// - `new(id: u32)`: 创建新实例（如果有 id 字段）
/// - `get_xxx()`: 获取 xxx 字段的引用
/// - `set_xxx()`: 设置 xxx 字段的值
///
/// 这是一个简化的实现，真实项目会更复杂
#[proc_macro_derive(CRUD)]
pub fn crud_derive(input: TokenStream) -> TokenStream {
    let input = parse_macro_input!(input as DeriveInput);
    let name = &input.ident;

    // 获取字段
    let fields = match &input.data {
        Data::Struct(data) => match &data.fields {
            Fields::Named(fields) => &fields.named,
            _ => {
                return syn::Error::new_spanned(name, "CRUD requires named fields")
                    .to_compile_error()
                    .into();
            }
        },
        _ => {
            return syn::Error::new_spanned(name, "CRUD only works on structs")
                .to_compile_error()
                .into();
        }
    };

    // 查找 id 字段
    let id_field = fields.iter().find(|f| {
        f.ident.as_ref().map_or(false, |i| i == "id")
    });

    let (id_type, has_id) = match id_field {
        Some(field) => {
            let ty = &field.ty;
            (quote!(#ty), true)
        }
        None => (quote!(u32), false),
    };

    // 生成 getter 和 setter
    let getters_setters = fields.iter().map(|f| {
        let ident = f.ident.as_ref().unwrap();
        let ident_str = ident.to_string();
        let setter_name = syn::Ident::new(&format!("set_{}", ident_str), ident.span());
        let ty = &f.ty;

        quote! {
            pub fn #ident(&self) -> &#ty {
                &self.#ident
            }

            pub fn #setter_name(&mut self, value: #ty) {
                self.#ident = value;
            }
        }
    });

    // 生成 new 函数
    let new_fn = if has_id {
        quote! {
            pub fn new(id: #id_type) -> Self {
                Self {
                    id,
                    ..::std::default::Default::default()
                }
            }
        }
    } else {
        quote! {
            pub fn new() -> Self {
                ::std::default::Default::default()
            }
        }
    };

    let expanded = quote! {
        impl #name {
            #new_fn
            #(#getters_setters)*
        }
    };

    TokenStream::from(expanded)
}

// ============================================================================
// 使用示例
// ============================================================================

// 使用这些 derive 宏的示例（在其他 crate 中）：
//
// use m6_project::{AutoDisplay, CRUD};
//
// #[derive(AutoDisplay, Default)]
// struct Example { value: i32, name: String }
//
// #[derive(CRUD, Default)]
// struct User { id: u32, name: String, email: String }
//
// fn main() {
//     let ex = Example { value: 42, name: "test".to_string() };
//     println!("{}", ex);
//
//     let mut user = User::new(42);
//     user.set_name("Alice".to_string());
// }
