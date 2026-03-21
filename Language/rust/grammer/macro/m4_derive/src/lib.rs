//! # M4: 过程宏入门 - derive 宏
//!
//! 本模块演示如何编写 derive 过程宏。
//!
//! 过程宏在编译期接收 TokenStream，处理后再返回 TokenStream。
//! 与声明宏不同，过程宏可以访问完整的语法树。

extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, DeriveInput, Data, DataStruct};

// ============================================================================
// Day 1: 过程宏基础
// ============================================================================

/// 过程宏的类型：
/// 1. derive 宏 - #[derive(MyTrait)]
/// 2. function-like 宏 - my_macro!(args)
/// 3. attribute 宏 - #[my_macro]
///
/// TokenStream 是编译器提供的抽象，表示 token 序列。

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

// Note: Hello trait 应该在使用者的代码中定义，例如：
// pub trait Hello {
//     fn hello(&self);
// }

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
        Data::Struct(DataStruct { fields, .. }) => fields,
        _ => {
            return syn::Error::new_spanned(
                name,
                "Describe derive only works on structs",
            )
            .to_compile_error()
            .into();
        }
    };

    // 收集字段名称用于生成描述
    let field_names: Vec<_> = fields
        .iter()
        .filter_map(|f| f.ident.as_ref())
        .collect();

    // 生成实现
    let expanded = quote! {
        impl Describe for #name {
            fn describe(&self) -> String {
                let mut description = format!("{} {{ ", stringify!(#name));
                #(
                    description.push_str(&format!("{}: {:?}, ", stringify!(#field_names), self.#field_names));
                )*
                description.push_str("}");
                description
            }
        }
    };

    TokenStream::from(expanded)
}

// Note: Describe trait 应该在使用者的代码中定义，例如：
// pub trait Describe {
//     fn describe(&self) -> String;
// }

// ============================================================================
// Day 3: Builder 模式 derive
// ============================================================================

/// Builder 模式 derive 宏
#[proc_macro_derive(Builder)]
pub fn builder_derive(input: TokenStream) -> TokenStream {
    let input = parse_macro_input!(input as DeriveInput);
    let name = &input.ident;
    let builder_name = format!("{}Builder", name);
    let builder_ident = syn::Ident::new(&builder_name, name.span());

    let fields = match &input.data {
        Data::Struct(DataStruct { fields, .. }) => fields,
        _ => {
            return syn::Error::new_spanned(name, "Builder only works on structs")
                .to_compile_error()
                .into();
        }
    };

    let field_idents: Vec<_> = fields.iter().filter_map(|f| f.ident.as_ref()).collect();
    let field_types: Vec<_> = fields
        .iter()
        .map(|f| &f.ty)
        .collect();

    let expanded = quote! {
        impl #name {
            pub fn builder() -> #builder_ident {
                #builder_ident::default()
            }
        }

        #[derive(Default)]
        pub struct #builder_ident {
            #(
                #field_idents: Option<#field_types>,
            )*
        }

        impl #builder_ident {
            #(
                pub fn #field_idents(mut self, value: #field_types) -> Self {
                    self.#field_idents = Some(value);
                    self
                }
            )*

            pub fn build(self) -> Result<#name, String> {
                Ok(#name {
                    #(
                        #field_idents: self.#field_idents.ok_or_else(|| {
                            format!("Field `{}` is missing", stringify!(#field_idents))
                        })?,
                    )*
                })
            }
        }
    };

    TokenStream::from(expanded)
}
