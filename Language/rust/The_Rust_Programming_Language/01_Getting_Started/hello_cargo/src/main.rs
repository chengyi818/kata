#[derive(Debug, PartialEq)]
struct Employee {
    name: String,
    age: u8,
    title: String,
}

impl Employee {
    pub fn new(name: String, age: u8, title: String) -> Self {
        Self { name, age, title }
    }
}

fn main() {
    let tyr = Employee::new("Tyr".to_owned(), 18, "CFO".to_string());
    let lindsey = Employee::new("Lindsey".to_owned(), 8, "CEO".to_string());
    let rosie = Employee::new("Rosie".to_owned(), 4, "CPO".to_string());
    println!("tyr: {:?}", tyr);
    let mut employees = vec![tyr, lindsey, rosie];

    fix_age(&mut employees);

    // 我们希望在 fix_age 后还能使用 employees
    println!("employees: {:?}", employees);
    assert_eq!(
        employees,
        &[
            Employee::new("Tyr".to_owned(), 18, "CFO".to_owned()),
            Employee::new("Lindsey".to_owned(), 8, "CEO".to_owned()),
            Employee::new("Rosie".to_owned(), 14, "CPO".to_owned())
        ]
    )
}

fn fix_age(employees: &mut Vec<Employee>) {
    employees
        .iter_mut()
        .filter(|e| e.age < 8)
        .for_each(|e| e.age += 10);
}
