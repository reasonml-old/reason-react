/**
 * Page component.
 * vim: set ft=rust:
 * vim: set ft=reason:
 */
module Page = {
  include ReactRe.Component.Stateful;
  type props = unit;
  type state = {clicks: int};
  let name = "Page";
  let getInitialState props => {clicks: 0};
  let handleClick event {state} => Some {clicks: state.clicks + 2};
  let render {state, updater} =>
    <div style={"color": "#444444", "webkitUserSelect": "none", "paddingTop": "40px", "fontSize": "68px", "fontFamily": "Montserrat", "textAlign":"center"}>
      (ReactRe.stringToElement ("REASON REACT"))
      <Logo message="Hello!" />
    </div>;
};

include ReactRe.CreateComponent Page;

let createElement children => wrapProps () children;
