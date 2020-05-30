use syn::{parse_macro_input, DeriveInput};

extern crate proc_macro;
use proc_macro::TokenStream;

#[proc_macro_derive(Widget)]
pub fn derive_widget_impl(input: TokenStream) -> TokenStream {
    let item = parse_macro_input!(input as DeriveInput);
    format!(
"impl Deref for {name} {{
    type Target = WidgetData;

    fn deref(&self) -> &Self::Target {{
        &self.0
    }}
}}

impl DerefMut for {name} {{
    fn deref_mut(&mut self) -> &mut Self::Target {{
        &mut self.0
    }}
}}

impl Widget for {name} {{}}
    ", name=item.ident).parse().unwrap()
}
