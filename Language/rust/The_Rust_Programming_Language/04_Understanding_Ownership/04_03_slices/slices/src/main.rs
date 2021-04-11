#[macro_use]
extern crate t_bang;
use t_bang::*;

fn first_word(s: &str) -> usize {
    let s_type = t!(s);
    println!("s_type: {}", s_type);

    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return i;
        }
    }

    s.len()
}

fn main() {
    let s = String::from("hello world");
    first_word(&s);

    let hello = &s[..5];
    let world = &s[6..11];
    println!("{} {}", hello, world);
}

fn second_word(s: &String) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }

    &s[..]
}
