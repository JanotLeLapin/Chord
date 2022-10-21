use yew::prelude::*;

#[function_component(App)]
pub fn app() -> Html {
    html! {
        <main>
            <h1>{ "Welcome to Chord" }</h1>
            <p>{ "An open-source Discord client implementation, written in Rust" }</p>
        </main>
    }
}

