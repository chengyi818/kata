#[derive(Debug)]
#[allow(dead_code)]
enum Gender {
    Unspecified = 0,
    Male = 1,
    Female = 2,
}

#[derive(Debug, Copy, Clone)]
struct UserId(u64);

#[derive(Debug, Copy, Clone)]
struct TopicId(u64);

#[derive(Debug)]
struct User {
    id: UserId,
    name: String,
    gender: Gender,
}

#[derive(Debug)]
struct Topic {
    id: TopicId,
    name: String,
    owner: UserId,
}

impl Topic {
    fn show(&self) {
        println!("id: {:?}", self.id.0);
    }
}

#[derive(Debug)]
enum Event {
    Join(UserId, TopicId),
    Leave(UserId, TopicId),
    Message(UserId, TopicId, String),
}

fn main() {
    let alice = User {
        id: UserId(1),
        name: "alice".to_string(),
        gender: Gender::Female,
    };
    let bob = User {
        id: UserId(2),
        name: "bob".to_string(),
        gender: Gender::Male,
    };
    let topic = Topic {
        id: TopicId(1),
        name: "rust".into(),
        owner: UserId(1),
    };
    topic.show();
    let e1 = Event::Join(alice.id, topic.id);
    let e2 = Event::Leave(bob.id, topic.id);
    let e3 = Event::Message(alice.id, topic.id, "hello".into());

    println!("{:?}, {:?}, {:?}", e1, e2, e3);
}
