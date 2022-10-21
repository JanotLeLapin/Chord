use chord_api::{auth,user};

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

    for id in vec!["969296752131842178", "437953881914474523", "539547679097749566"] {
        let user = user::fetch_user(&client, id).await.unwrap();
        println!(
            "{}#{} {}",
            user.get_name(),
            user.get_discriminator(),
            user.get_avatar().unwrap_or("no avatar :(".to_string()),
        );
    }
}

