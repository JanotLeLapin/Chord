use serde::Deserialize;

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

