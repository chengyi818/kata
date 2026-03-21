//! # cli-derive - 命令行解析过程宏
//!
//! 这是 M6 综合实战项目的过程宏实现 crate。
//! 实现了 `#[derive(Parser)]` derive 宏。

extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, DeriveInput, Data, DataStruct, Fields, Attribute};

/// 从属性列表中提取指定名称的属性值
fn parse_attr_value(attrs: &[Attribute], name: &str) -> Option<String> {
    for attr in attrs {
        if attr.path().is_ident(name) {
            if let Ok(meta) = attr.meta.require_list() {
                let nested = &meta.tokens;
                // 简单解析 name = "value" 格式
                let content = nested.to_string();
                for part in content.split(',') {
                    let part = part.trim();
                    if part.starts_with("name") {
                        if let Some(eq_pos) = part.find('=') {
                            let value = part[eq_pos + 1..].trim().trim_matches('"');
                            return Some(value.to_string());
                        }
                    }
                }
            }
        }
    }
    None
}

/// 解析嵌套的 name-value 对，如 `#[arg(short = "n", long = "name")]`
fn parse_nested_attr_value(attr: &Attribute, key: &str) -> Option<String> {
    if let Ok(meta) = attr.meta.require_list() {
        let content = meta.tokens.to_string();
        for part in content.split(',') {
            let part = part.trim();
            if part.starts_with(key) {
                if let Some(eq_pos) = part.find('=') {
                    let value = part[eq_pos + 1..].trim().trim_matches('"');
                    return Some(value.to_string());
                }
            }
        }
    }
    None
}

/// 为结构体实现命令行解析功能
///
/// 支持以下属性：
/// - `#[command(name = "...")]` - 命令元数据
/// - `#[arg(short = "...", long = "...", default_value = "...")]` - 参数元数据
#[proc_macro_derive(Parser, attributes(command, arg))]
pub fn derive_parser(input: TokenStream) -> TokenStream {
    let input = parse_macro_input!(input as DeriveInput);
    let name = &input.ident;

    // 解析 command 属性
    let command_name = parse_attr_value(&input.attrs, "command")
        .unwrap_or_else(|| name.to_string().to_lowercase());

    // 确保是结构体
    let fields = match &input.data {
        Data::Struct(DataStruct { fields: Fields::Named(fields), .. }) => &fields.named,
        Data::Struct(DataStruct { fields: Fields::Unit, .. }) => {
            // 单元结构体，生成简化版实现
            let expanded = quote! {
                impl #name {
                    pub fn parse() -> Self {
                        Self
                    }

                    pub fn parse_from(_args: &[&str]) -> Self {
                        Self
                    }

                    pub fn command_name() -> &'static str {
                        #command_name
                    }
                }
            };
            return TokenStream::from(expanded);
        }
        _ => {
            return syn::Error::new_spanned(
                name,
                "Parser derive only supports structs with named fields or unit structs",
            )
            .to_compile_error()
            .into();
        }
    };

    // 为每个字段生成解析代码
    let field_parsers: Vec<_> = fields
        .iter()
        .map(|field| {
            let field_name = field.ident.as_ref().unwrap();
            let field_type = &field.ty;

            // 解析 arg 属性
            let short = field
                .attrs
                .iter()
                .find(|a| a.path().is_ident("arg"))
                .and_then(|a| parse_nested_attr_value(a, "short"));

            let long = field
                .attrs
                .iter()
                .find(|a| a.path().is_ident("arg"))
                .and_then(|a| parse_nested_attr_value(a, "long"));

            let default_value = field
                .attrs
                .iter()
                .find(|a| a.path().is_ident("arg"))
                .and_then(|a| parse_nested_attr_value(a, "default_value"));

            let long_name = long.unwrap_or_else(|| field_name.to_string());
            let long_flag = format!("--{}", long_name);

            // 根据是否有短选项和默认值生成不同的代码
            let short_parsing = match &short {
                Some(s) => {
                    let short_flag = format!("-{}", s);
                    quote! {
                        // 检查短选项
                        let __short_flag = #short_flag;
                        for (i, arg) in __cli_args.iter().enumerate() {
                            if arg == __short_flag {
                                if let Some(v) = __cli_args.get(i + 1) {
                                    value = v.parse::<#field_type>().ok();
                                }
                            }
                        }
                    }
                }
                None => quote! {},
            };

            // 根据是否有默认值生成不同的代码
            if let Some(default) = default_value {
                let default_lit = syn::LitStr::new(&default, proc_macro2::Span::call_site());
                quote! {
                    #field_name: {
                        let mut value = #default_lit.parse::<#field_type>().ok();
                        let __long_flag = #long_flag;
                        for (i, arg) in __cli_args.iter().enumerate() {
                            if arg == __long_flag {
                                if let Some(v) = __cli_args.get(i + 1) {
                                    value = v.parse::<#field_type>().ok();
                                }
                            }
                        }
                        #short_parsing
                        value.unwrap_or_else(|| #default_lit.parse::<#field_type>().unwrap())
                    }
                }
            } else {
                quote! {
                    #field_name: {
                        let mut value = None;
                        let __long_flag = #long_flag;
                        for (i, arg) in __cli_args.iter().enumerate() {
                            if arg == __long_flag {
                                if let Some(v) = __cli_args.get(i + 1) {
                                    value = Some(v.parse::<#field_type>()
                                        .expect(&format!("Invalid value for {}", __long_flag)));
                                }
                            }
                        }
                        #short_parsing
                        value.expect(&format!("Missing required argument: {}", __long_flag))
                    }
                }
            }
        })
        .collect();

    // 生成帮助信息方法
    let help_entries: Vec<_> = fields
        .iter()
        .map(|field| {
            let long = field
                .attrs
                .iter()
                .find(|a| a.path().is_ident("arg"))
                .and_then(|a| parse_nested_attr_value(a, "long"))
                .unwrap_or_else(|| field.ident.as_ref().unwrap().to_string());

            let short = field
                .attrs
                .iter()
                .find(|a| a.path().is_ident("arg"))
                .and_then(|a| parse_nested_attr_value(a, "short"));

            let short_display = match short {
                Some(s) => format!("-{}", s),
                None => String::new(),
            };

            // 提取类型名称作为字符串（用于帮助信息）
            let type_str = format!("{}", quote!(#field.ty));

            quote! {
                println!("  --{} {}\t({})", #long, #short_display, #type_str);
            }
        })
        .collect();

    let expanded = quote! {
        impl #name {
            pub fn parse() -> Self {
                let __cli_args: Vec<String> = std::env::args().skip(1).collect();

                // 处理帮助请求
                if __cli_args.contains(&"--help".to_string()) || __cli_args.contains(&"-h".to_string()) {
                    Self::print_help();
                    std::process::exit(0);
                }

                Self {
                    #(#field_parsers),*
                }
            }

            pub fn parse_from(__raw_args: &[&str]) -> Self {
                let __cli_args: Vec<String> = __raw_args.iter().map(|s| s.to_string()).collect();
                Self {
                    #(#field_parsers),*
                }
            }

            pub fn command_name() -> &'static str {
                #command_name
            }

            fn print_help() {
                println!("Usage: {} [OPTIONS]", #command_name);
                println!("\nOptions:");
                #(#help_entries)*
                println!("  -h, --help\tPrint help information");
            }
        }
    };

    TokenStream::from(expanded)
}
