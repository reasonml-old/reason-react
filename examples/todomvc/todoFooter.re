module TodoFooter = {
  include ReactRe.Component;
  let name = "TodoFooterRe";
  type showingState =
    | AllTodos
    | ActiveTodos
    | CompletedTodos;
  type props = {
    count: int,
    completedCount: int,
    nowShowing: showingState,
    onClearCompleted: ReactRe.event => unit
  };
  let render {props} => {
    let activeTodoWord = Utils.pluralize props.count "item";
    let clearButton =
      props.completedCount > 0 ?
        <button className="clear-completed" onClick=props.onClearCompleted>
          (ReactRe.toElement "Clear completed")
        </button> :
        ReactRe.nullElement;
    let (all, active, completed) =
      switch props.nowShowing {
      | AllTodos => ("selected", "", "")
      | ActiveTodos => ("", "selected", "")
      | CompletedTodos => ("", "", "selected")
      };
    <footer className="footer">
      <span className="todo-count">
        <strong> (ReactRe.toElement props.count) </strong>
        (ReactRe.toElement (" " ^ activeTodoWord ^ " left"))
      </span>
      <ul className="filters">
        <li> <a href="#/" className=all> (ReactRe.toElement "All") </a> </li>
        (ReactRe.toElement " ")
        <li> <a href="#/active" className=active> (ReactRe.toElement "Active") </a> </li>
        (ReactRe.toElement " ")
        <li> <a href="#/completed" className=completed> (ReactRe.toElement "Completed") </a> </li>
      </ul>
      clearButton
    </footer>
  };
};

include ReactRe.CreateComponent TodoFooter;

let createElement ::count ::completedCount ::nowShowing ::onClearCompleted =>
  wrapProps {count, completedCount, nowShowing, onClearCompleted};
