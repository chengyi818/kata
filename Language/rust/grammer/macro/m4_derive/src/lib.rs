//! # M4: 过程宏入门 - derive 宏
//!
//! 本模块演示如何编写 derive 过程宏。
//!
//! 过程宏在编译期接收 TokenStream，处理后再返回 TokenStream。
//! 与声明宏不同，过程宏可以访问完整的语法树。
//!
//! 宏 2.0 的重要特性：
//! - 统一 TokenStream 流水线：`macro_rules!`、`derive`、`proc_macro` 共用相同机制
//! - IDE 支持：rust-analyzer 可展示宏展开、Clippy 可对展开后代码做 lint
//!
//! **注意**：过程宏 crate 不能在同 crate 中使用自己的宏。
//! 测试应在单独的 integration test crate 中进行。

extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, DeriveInput, Data, DataStruct, Fields};

// ============================================================================
// Day 1: 过程宏基础
// ============================================================================

/// 过程宏的类型：
/// 1. derive 宏 - #[derive(MyTrait)]
/// 2. function-like 宏 - my_macro!(args)
/// 3. attribute 宏 - #[my_macro]
///
/// TokenStream 是编译器提供的抽象，表示 token 序列。
/// 在宏 2.0 统一流水线中，所有宏类型都操作 TokenStream。

/// 简单的 derive 宏：添加一个 `Hello` trait
#[proc_macro_derive(Hello)]
pub fn hello_derive(input: TokenStream) -> TokenStream {
    // 1. 解析输入为语法树
    let input = parse_macro_input!(input as DeriveInput);

    // 2. 获取结构体名称
    let name = &input.ident;

    // 3. 生成实现代码
    let expanded = quote! {
        impl Hello for #name {
            fn hello(&self) {
                println!("Hello, I am {}!", stringify!(#name));
            }
        }
    };

    // 4. 返回 TokenStream
    TokenStream::from(expanded)
}

// ============================================================================
// Day 2: 解析结构体字段
// ============================================================================

/// 这个 derive 宏可以访问结构体的字段
#[proc_macro_derive(Describe)]
pub fn describe_derive(input: TokenStream) -> TokenStream {
    let input = parse_macro_input!(input as DeriveInput);

    let name = &input.ident;

    // 检查是否是结构体
    let fields = match &input.data {
        Data::Struct(DataStruct { fields: Fields::Named(fields), .. }) => &fields.named,
        _ => {
            return syn::Error::new_spanned(
                name,
                "Describe derive only works on structs with named fields",
            )
            .to_compile_error()
            .into();
        }
    };

    // 获取字段名称和生成描述字符串的代码
    let field_descs = fields.iter().map(|f| {
        let name = &f.ident;
        quote! {
            description.push_str(&format!("{}: {:?}, ", stringify!(#name), self.#name));
        }
    });

    // 生成实现
    let expanded = quote! {
        impl Describe for #name {
            fn describe(&self) -> String {
                let mut description = String::new();
                #(#field_descs)*
                description
            }
        }
    };

    TokenStream::from(expanded)
}

// ============================================================================
// Day 3: Builder 模式 derive
// ============================================================================

/// Builder 模式 derive 宏
///
/// 宏 2.0 提示：生成的代码走统一 TokenStream 流水线，
/// 可以被 IDE 正确识别和跳转
#[proc_macro_derive(Builder)]
pub fn builder_derive(input: TokenStream) -> TokenStream {
    let input = parse_macro_input!(input as DeriveInput);
    let name = &input.ident;
    let builder_name = format!("{}Builder", name);
    let builder_ident = syn::Ident::new(&builder_name, name.span());

    let fields = match &input.data {
        Data::Struct(DataStruct { fields: Fields::Named(fields), .. }) => &fields.named,
        _ => {
            return syn::Error::new_spanned(name, "Builder only works on structs with named fields")
                .to_compile_error()
                .into();
        }
    };

    let field_idents: Vec<_> = fields.iter().map(|f| &f.ident).collect();
    let field_types: Vec<_> = fields.iter().map(|f| &f.ty).collect();

    // 生成 builder 方法
    let builder_methods = field_idents.iter().zip(&field_types).map(|(ident, ty)| {
        quote! {
            pub fn #ident(mut self, value: #ty) -> Self {
                self.#ident = Some(value);
                self
            }
        }
    });

    // 生成 build 方法中的字段检查
    let build_fields = field_idents.iter().map(|ident| {
        quote! {
            #ident: self.#ident.ok_or_else(|| {
                format!("Field `{}` is missing", stringify!(#ident))
            })?
        }
    });

    let expanded = quote! {
        impl #name {
            pub fn builder() -> #builder_ident {
                #builder_ident::default()
            }
        }

        #[derive(Default)]
        pub struct #builder_ident {
            #(#field_idents: Option<#field_types>,)*
        }

        impl #builder_ident {
            #(#builder_methods)*

            pub fn build(self) -> Result<#name, String> {
                Ok(#name {
                    #(#build_fields,)*
                })
            }
        }
    };

    TokenStream::from(expanded)
}

// ============================================================================
// 使用说明
// ============================================================================

// 使用这些 derive 宏的示例（在其他 crate 中）：
//
// use m4_derive::{Hello, Describe, Builder};
//
// #[derive(Hello)]
// struct Person { name: String, age: u32 }
//
// #[derive(Describe)]
// struct Point { x: i32, y: i32 }
//
// #[derive(Builder)]
// struct Config { host: String, port: u16 }
//
// fn main() {
//     Person { name: "Alice".to_string(), age: 30 }.hello();
//     Point { x: 10, y: 20 }.describe();
//     Config::builder().host("localhost".to_string()).port(8080).build().unwrap();
// }
