#[allow(dead_code)]
struct Cat {
    name: String,
    age: i32,
}
impl Cat {
    fn new(name: String, age: i32) -> Self {
        Self { name, age }
    }
}

trait Animal {
    fn name(&self) -> &'static str;
    // fn by_ref(&self) -> &Self;
}

impl Animal for Cat {
    fn name(&self) -> &'static str {
        "Cat"
    }

    // fn by_ref(&self) -> &Self
    // where
    //     Self: Sized,
    // {
    //     self
    // }
}

fn main() {
    let cat = Cat::new("kitty".to_string(), 2);
    let animal: &dyn Animal = &cat;
    println!("cat: {}", animal.name());
}
