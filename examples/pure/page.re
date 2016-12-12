/**
 * Page component.
 */
open ReactRe;

include
  ReactRe.CreateComponent {
    include ReactRe.Component;
    type props = unit;
    type state = {clicks: int};
    type jsPropTypes = string;
    let name = "Page";
    let getInitialState props => {clicks: 0};
    let handleClick event {state} => Some {clicks: state.clicks + 2};
    let render {state, updater} =>
      <div>
        <button onClick=(updater handleClick)>
          (ReactRe.toElement ("Clicked " ^ string_of_int state.clicks ^ " time(s)"))
        </button>
        <Logo message="Hello!" />
        <LifecycleTester incrOnDidMount=true initialCount=10 incr=3 />
      </div>;
  };

let createElement children => wrapProps () children;
