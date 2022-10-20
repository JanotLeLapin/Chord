use chord_api::{auth,message};

#[tokio::main]
pub async fn main() {
    // Read chord credentials file
    let mut path = dirs::config_dir().unwrap();
    path.push("chord");
    path.push("credentials.toml");

    let creds = std::fs::read_to_string(path).expect("Missing credentials file at ~/.config/chord/credentials.toml.")
        .parse::<toml::Value>().expect("Could not parse credentials file.");

    let login = creds["login"].as_str().expect("Could not get login in credentials file.");
    let password = creds["password"].as_str().expect("Could not get password in credentials file.");

    // Fetch authorization token from discord with credentials
    let client = auth::login(login, password).await.unwrap();

    // Get messages from some channel and print them out
    let messages = message::fetch_messages(&client, "973573920613597207", 50).await.unwrap();

    for i in (1..messages.len()).rev() {
        let msg = &messages[i-1];

        let author = msg.get_author();
        if author.get_id() == messages[i].get_author().get_id() {
            println!("{}", msg.get_content());
        } else {
            println!("\n{}#{} à {}:\n{}", author.get_name(), author.get_discriminator(), msg.get_timestamp().to_string(), msg.get_content());
        }
    }
}

