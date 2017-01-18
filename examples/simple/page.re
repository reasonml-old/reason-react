module Page = {
  include ReactRe.Component;
  type props = {message: string};
  let name = "Page";
  let handleClick {props} event => {
    Js.log "clicked!";
    None
  };
  let render {props, updater} =>
    <div onClick=(updater handleClick)> (ReactRe.stringToElement props.message) </div>;
};

include ReactRe.CreateComponent Page;

let createElement ::message ::children => wrapProps {message: message} ::children;
