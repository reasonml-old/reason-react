/**
 * Page component.
 */
open ReactRe;

type props = {incrOnDidMount: bool, initialCount: int, incr: int};

include
  ReactRe.CreateComponent {
    include ReactRe.Component;
    type nonrec props = props;
    type state = {clicks: int};
    let name = "LifecycleTester";
    let getInitialState props => {clicks: props.initialCount};
    let handleClick event {props, state} => Some {clicks: state.clicks + props.incr};
    let componentDidMount {props, state} => {
      print_string "IN MOUNT";
      print_newline ();
      props.incrOnDidMount ? Some {...state, clicks: state.clicks + props.incr} : None
    };
    let render {state, updater} =>
      <div>
        <button onClick=(updater handleClick)>
          (ReactRe.toElement ("Clicked " ^ string_of_int state.clicks ^ " time(s)"))
        </button>
        <Logo message="Hello!" />
      </div>;
  };

let createElement ::incrOnDidMount=false ::incr=0 ::initialCount=0 children =>
  wrapProps {incrOnDidMount, initialCount, incr} children;
