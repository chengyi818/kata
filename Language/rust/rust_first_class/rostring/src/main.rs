use std::ops::Deref;
use std::{borrow::Borrow, sync::Arc, thread};

#[derive(Debug)]
enum RoString {
    Static(&'static str),
    Shared(Arc<String>),
}

impl From<&'static str> for RoString {
    fn from(s: &'static str) -> Self {
        RoString::Static(s)
    }
}

impl From<String> for RoString {
    fn from(s: String) -> Self {
        RoString::Shared(Arc::new(s))
    }
}
impl PartialEq<&str> for RoString {
    fn eq(&self, other: &&str) -> bool {
        match self {
            RoString::Static(s) => *s == *other,
            RoString::Shared(s) => s.as_str() == *other,
        }
    }
}

impl Clone for RoString {
    fn clone(&self) -> Self {
        match self {
            RoString::Static(s) => RoString::Static(*s),
            RoString::Shared(s) => RoString::Shared(s.clone()),
        }
    }
}

impl Deref for RoString {
    type Target = str;

    fn deref(&self) -> &Self::Target {
        match self {
            RoString::Static(s) => *s,
            RoString::Shared(s) => s,
        }
    }
}

fn main() {
    // 需要实现 From<&'static str>，让 RoString 可以从 &'static str 构造
    let s = RoString::from("hello world");

    let s1 = String::from("goodbye world");
    // // 需要实现 From<String>
    let s1 = RoString::from(s1);

    println!("s: {:?}, s1: {:?}", s, s1);

    // // 需要实现 PartialEq trait
    assert_eq!(s, "hello world");

    // 需要手工实现 clone - clone 时，检查 RoString 现在在什么状态
    // 如果是 Static，就直接创建一个新的 RoString::Static，使用已有的 &'static str
    let s_cloned = s.clone();

    // 如果是 Shared，则对 Arc<String> clone
    let s1_cloned = s1.clone();

    // 这样在跨线程传递时，无论 Static / Shared，都可以正常使用
    let handle = thread::spawn(move || {
        assert_eq!(s_cloned, "hello world");
        assert_eq!(s1_cloned, "goodbye world");
        println!("s_cloned: {:?}, s1_cloned: {:?}", s_cloned, s1_cloned);
    });

    handle.join().unwrap();

    // // 这里需要 Deref trait 实现
    assert_eq!(&s[..5], "hello");
    assert_eq!(&s1[..5], "goodb");
}
