use std::fmt::Display;
use std::error::Error;

use serde::Deserialize;
use serde_json::json;

use crate::URL;

#[derive(Deserialize)]
pub struct LoginResponse {
    token: String,
}

#[derive(Debug, Default, Clone)]
pub struct LoginError;
impl Display for LoginError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "invalid credentials")
    }
}
impl Error for LoginError {}

pub async fn login(login: &str, password: &str) -> Result<reqwest::Client, Box<dyn Error>> {
    let res = reqwest::Client::new()
        .post(format!("{}/auth/login", URL))
        .body(json!({
            "login": login,
            "password": password,
        }).to_string())
        .header("Content-Type", "application/json")
        .send().await?;

    let token = res.json::<LoginResponse>().await?.token;

    let mut headers = reqwest::header::HeaderMap::new();
    headers.insert("Content-Type", "application/json".parse().unwrap());
    headers.insert("Authorization", token.parse().unwrap());

    let client = reqwest::ClientBuilder::new()
        .default_headers(headers)
        .build()?;

    match 200 {
        200 => Ok(client),
        _ => Err(Box::new(LoginError::default()))
    }
}

