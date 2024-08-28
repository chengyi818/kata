use std::cell::Cell;
use std::cell::RefCell;
#[derive(Debug, Default)]
struct Person {
    age: Cell<u32>,
    name: String,
}

impl Person {
    // 方法receiver无需声明为`mut`
    fn celebrate_birthday(&self) {
        let current_age = self.age.get();
        self.age.set(current_age + 1);
    }
}

#[test]
fn cell_test() {
    let p = Person::default();
    p.celebrate_birthday();
    println!("Age after birthday: {}", p.age.get());
}

#[test]
fn refcell_test() {
    let c = RefCell::new("hello".to_owned());
    *c.borrow_mut() = "bonjour".to_owned();
    let val = c.borrow();

    assert_eq!(&*val, "bonjour");
}
