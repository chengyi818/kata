use std::{fmt, ops::Deref, str};

const MYVEC_MAX_LEN: usize = 30;

// MyString 里，String 有 3 个 word，供 24 字节，所以它以 8 字节对齐
// 所以 enum 的 tag + padding 最少 8 字节，整个结构占 32 字节。
// MiniString 可以最多有 30 字节（再加上 1 字节长度和 1字节 tag），就是 32 字节.
struct MiniVec<T> {
    len: u8,
    data: [T; MYVEC_MAX_LEN],
}

impl<T> MiniVec<T> {
    // 这里 new 接口不暴露出去，保证传入的 v 的字节长度小于等于 30
    fn new() -> Self {
        let data = [T; MYVEC_MAX_LEN];
        Self {
            len: 0,
            data,
        }
    }
}

impl<T> Deref for MiniVec<T> {
    type Target = [T];

    fn deref(&self) -> &[T] {
        unsafe { slice::from_raw_parts(&self.data, self.len) }
    }
}

impl<T> fmt::Debug for MiniVec<T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        // 这里由于实现了 Deref trait，可以直接得到一个 &str 输出
        write!(f, "{}", self.deref())
    }
}

#[derive(Debug)]
enum MyVec<T> {
    Inline(MiniVec<T>),
    Standard(Vec<T>),
}

// 实现 Deref 接口对两种不同的场景统一得到 &str
impl<T> Deref for MyVec<T> {
    type Target = [T];

    fn deref(&self) -> &[T] {
        match *self {
            MyVec::Inline(ref v) => v.deref(),
            MyVec::Standard(ref v) => v.deref(),
        }
    }
}

impl fmt::Display for MyString {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.deref())
    }
}

impl<T> MyVec<T> {
    pub fn new() -> Self {
        Self::Inline {
            MiniVec::new()
        }
    }
}

fn main() {
    let mut m = MyVec::new();
    m.push(1);
    println!("m: {}", m);
}