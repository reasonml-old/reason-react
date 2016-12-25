let escapeKey = 27;

let enterKey = 13;

type todo = {id: string, title: string, completed: bool};

module TodoItem = {
  include ReactRe.Component.Stateful.InstanceVars;
  let name = "TodoItemRe";
  type props = {
    todo: todo,
    editing: bool,
    onDestroy: unit => unit,
    onSave: string => unit,
    onEdit: unit => unit,
    onToggle: ReactRe.event => unit,
    onCancel: ReactRe.event => unit
  };
  type state = {editText: string};
  type instanceVars = {mutable editFieldRef: option ReactRe.reactRef};
  let getInstanceVars () => {editFieldRef: None};
  let getInitialState props => {editText: props.todo.title};
  let handleSubmit event {props, state} =>
    switch (String.trim state.editText) {
    | "" =>
      props.onDestroy ();
      None
    | nonEmptyValue =>
      props.onSave nonEmptyValue;
      Some {editText: nonEmptyValue}
    };
  let handleEdit event {props} => {
    props.onEdit ();
    Some {editText: props.todo.title}
  };
  let handleKeyDown event ({props} as componentBag) => {
    let eventWhich = (ReactRe.eventToJsObj event)##which;
    if (eventWhich === escapeKey) {
      props.onCancel event;
      Some {editText: props.todo.title}
    } else if (
      eventWhich === enterKey
    ) {
      handleSubmit event componentBag
    } else {
      None
    }
  };
  let handleChange event {props} => props.editing ? Some {editText: event##target##value} : None;
  let setEditFieldRef r {instanceVars} => instanceVars.editFieldRef = Some r;

  /**
   * Safely manipulate the DOM after updating the state when invoking
   * `props.onEdit()` in the `handleEdit` method above.
   * For more info refer to notes at https://facebook.github.io/react/docs/component-api.html#setstate
   * and https://facebook.github.io/react/docs/component-specs.html#updating-componentdidupdate
   */
  let componentDidUpdate prevProps prevState {props, instanceVars} =>
    switch (prevProps.editing, props.editing, instanceVars.editFieldRef) {
    | (false, true, Some field) =>
      let node = ReactDOMRe.domElementToObj (ReactDOMRe.findDOMNode field);
      ignore (node##focus ());
      ignore (node##setSelectionRange node##value##length node##value##length);
      None
    | _ => None
    };
  let render {props, state, updater, refSetter} => {
    let {todo, editing, onDestroy, onToggle} = props;
    let className =
      [todo.completed ? "completed" : "", editing ? "editing" : ""] |> String.concat " ";
    <li className>
      <div className="view">
        <input className="toggle" type_="checkbox" checked=todo.completed onChange=onToggle />
        <label onDoubleClick=(updater handleEdit)> (ReactRe.stringToElement todo.title) </label>
        <button className="destroy" onClick=onDestroy />
      </div>
      <input
        ref=(refSetter setEditFieldRef)
        className="edit"
        value=state.editText
        onBlur=(updater handleSubmit)
        onChange=(updater handleChange)
        onKeyDown=(updater handleKeyDown)
      />
    </li>;
  };
};

include ReactRe.CreateComponent TodoItem;

let createElement ::todo ::editing ::onDestroy ::onSave ::onEdit ::onToggle ::onCancel =>
  wrapProps {todo, editing, onDestroy, onSave, onEdit, onToggle, onCancel};
