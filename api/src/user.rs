use std::fmt::Display;
use std::error::Error;

use serde::Deserialize;
use serde_json::json;

pub static URL: &str = "https://discord.com/api/v9";

#[derive(Deserialize, Debug)]
pub struct UserSettings {
    locale: String,
    theme: String,
}

#[derive(Deserialize, Debug)]
pub struct LoginResponse {
    token: String,
    user_settings: UserSettings,
    user_id: String,
}

#[derive(Debug, Default, Clone)]
pub struct LoginError;
impl Display for LoginError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "invalid credentials")
    }
}
impl Error for LoginError {}

pub async fn login(login: &str, password: &str) -> Result<LoginResponse, Box<dyn Error>> {
    let res = reqwest::Client::new()
        .post(format!("{}/auth/login", URL))
        .body(json!({
            "login": login,
            "password": password,
        }).to_string())
        .header("Content-Type", "application/json")
        .send().await?;

    match res.status().as_u16() {
        200 => Ok(res.json::<LoginResponse>().await?),
        _ => Err(Box::new(LoginError::default()))
    }
}

