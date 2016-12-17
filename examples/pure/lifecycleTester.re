/**
 * Page component.
 */
module LifecycleTester = {
  include ReactRe.Component;
  type props = {incrOnDidMount: bool, initialCount: int, incr: int};
  type state = {clicks: int};
  let name = "LifecycleTester";
  let getInitialState props => {clicks: props.initialCount};
  let handleClick event {props, state} => Some {clicks: state.clicks + props.incr};
  let componentDidMount {props, state} => {
    print_string "IN MOUNT";
    print_newline ();
    props.incrOnDidMount ? Some {clicks: state.clicks + props.incr} : None
  };
  let render {state, updater} =>
    <div>
      <button onClick=(updater handleClick)>
        (ReactRe.toElement ("Clicked " ^ string_of_int state.clicks ^ " time(s)"))
      </button>
      <Logo message="Hello!" />
    </div>;
};

include ReactRe.CreateComponent LifecycleTester;

let createElement ::incrOnDidMount=false ::incr=0 ::initialCount=0 children =>
  wrapProps {incrOnDidMount, initialCount, incr} children;
