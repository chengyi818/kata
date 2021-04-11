fn main() {
    //enum IpAddrKind {
    //V4,
    //V6,
    //}

    //struct IpAddr {
    //kind: IpAddrKind,
    //address: String,
    //}

    //let home = IpAddr {
    //kind: IpAddrKind::V4,
    //address: String::from("127.0.0.1"),
    //};

    //let loopback = IpAddr {
    //kind: IpAddrKind::V6,
    //address: String::from("::1"),
    //};

    //enum IpAddr {
    //V4(String),
    //V6(String),
    //}
    //let home = IpAddr::V4(String::from("127.0.0.1"));
    //let loopback = IpAddr::V6(String::from("::1"));

    enum IpAddr {
        V4(u8, u8, u8, u8),
        V6(String),
    }
    let home = IpAddr::V4(127, 0, 0, 1);
    let loopback = IpAddr::V6(String::from("::1"));

    let absent_num: Option<i32> = None;
    println!("{:#?}", absent_num);
}
