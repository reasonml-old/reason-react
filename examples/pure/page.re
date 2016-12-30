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
    <div>
      <button onClick=(updater handleClick)>
        (ReactRe.stringToElement ("Clicked " ^ string_of_int state.clicks ^ " time(s)"))
      </button>
      <Logo message="Hello!" />
      <LifecycleTester.StandardTester incrOnDidMount=true initialCount=10 incr=3 />
      <LifecycleTester.WithStatefulInstanceVars incrOnDidMount=true initialCount=10 incr=3 />
    </div>;
};

include ReactRe.CreateComponent Page;

let createElement ::children => wrapProps () ::children;
