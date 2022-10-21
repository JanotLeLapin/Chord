use std::error::Error;

use serde::Deserialize;

use crate::URL;

#[derive(Deserialize,Clone)]
pub struct User {
    id: String,
    username: String,
    discriminator: String,
    avatar: Option<String>,
}

impl User {
    pub fn get_id(&self) -> String { self.id.clone() }
    pub fn get_name(&self) -> String { self.username.clone() }
    pub fn get_discriminator(&self) -> String { self.discriminator.clone() }
    pub fn get_avatar(&self) -> Option<String> { self.avatar.clone() }
}

pub async fn fetch_current_user(client: &reqwest::Client) -> Result<User, Box<dyn Error>> {
    Ok(client.get(format!("{}/users/@me", URL))
        .send().await?
        .json::<User>().await?)
}

pub async fn fetch_user(client: &reqwest::Client, id: &str) -> Result<User, Box<dyn Error>> {
    Ok(client.get(format!("{}/users/{}", URL, id))
        .send().await?
        .json::<User>().await?)
}

