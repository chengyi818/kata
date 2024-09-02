use lazy_static::lazy_static;
use std::cell::RefCell;
use std::collections::HashMap;
use std::sync::{Arc, Mutex, RwLock};

static STATIC_VEC: RwLock<Vec<i32>> = RwLock::new(Vec::new());
lazy_static! {
    static ref STATIC_MAP: RwLock<HashMap<i32, i32>> = RwLock::new(HashMap::new());
}

fn main() {
    {
        let mut w = STATIC_VEC.write().unwrap();
        w.push(1);
    }
    {
        let mut w = STATIC_MAP.write().unwrap();
        w.insert(1, 1);
    }
    println!("{:?}", STATIC_VEC.read().unwrap());
    println!("{:?}", STATIC_MAP.read().unwrap());
}
