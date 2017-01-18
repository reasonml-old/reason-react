module Page = {
  include ReactRe.Component.InstanceVars;
  type props = {message: string};
  /* type state = {hello: int}; */
  /* let getInitialState props => {
       {hello: 1}
     }; */
  let name = "Page";
  let componentWillReceiveProps {props} ::nextProps => None;
  let handleClick {props} event => {
    Js.log "clicked!";
    None
  };
  let render {props, updater} =>
    <div onClick=(updater handleClick)> (ReactRe.stringToElement props.message) </div>;
  type instanceVars = {mutable foo: option int};
  let getInstanceVars () => {foo: None};
};

include ReactRe.CreateComponent Page;

let createElement ::message ::children => wrapProps {message: message} ::children;
