use std::error::Error;

use serde::Deserialize;

use chrono::{DateTime,NaiveDateTime};

use crate::URL;
use crate::user::User;

#[derive(Deserialize)]
pub struct Message {
    id: String,
    channel_id: String,
    author: User,
    content: String,
    timestamp: String,
    edited_timestamp: Option<String>,
    tts: bool,
    mention_everyone: bool,
    pinned: bool,
}

impl Message {
    pub fn get_id(&self) -> String { self.id.clone() }
    pub fn get_content(&self) -> String { self.content.clone() }
    pub fn get_author(&self) -> User { self.author.clone() }
    pub fn get_channel_id(&self) -> String { self.channel_id.clone() }
    pub fn get_timestamp(&self) -> NaiveDateTime { DateTime::parse_from_rfc3339(&self.timestamp).unwrap().naive_utc() }
    pub fn get_edited_timestamp(&self) -> Option<NaiveDateTime> { self.edited_timestamp.as_ref().map(|t| DateTime::parse_from_rfc3339(t).unwrap().naive_utc()) }
    pub fn is_tts(&self) -> bool { self.tts }
    pub fn mentions_everyone(&self) -> bool { self.mention_everyone }
    pub fn is_pinned(&self) -> bool { self.pinned }
}

pub async fn fetch_messages(client: &reqwest::Client, channel: &str, limit: u8) -> Result<Vec<Message>, Box<dyn Error>> {
    Ok(client.get(format!("{}/channels/{}/messages?limit={}", URL, channel, limit))
        .send().await?
        .json::<Vec<Message>>().await?)
}

