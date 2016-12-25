type router = Js.t {. init : (string => unit) [@bs.meth]};

external routerMake : _ => router = "Router" [@@bs.module "director"] [@@bs.new];

let enterKey = 13;

let namespace = "reason-react-todos";

let saveLocally todos => ReasonJs.LocalStorage.setItem namespace (ReasonJs.JSON.stringify todos);

module Top = {
  module TodoApp = {
    include ReactRe.Component.Stateful;
    let name = "TodoAppRe";
    type props = unit;
    type state = {
      nowShowing: TodoFooter.TodoFooter.showingState,
      editing: option string,
      newTodo: string,
      todos: list TodoItem.todo
    };
    let getInitialState props => {
      let todos =
        switch (Js.Null.to_opt (ReasonJs.LocalStorage.getItem namespace)) {
        | None => []
        | Some todos => ReasonJs.JSON.parse todos
        };
      {nowShowing: AllTodos, editing: None, newTodo: "", todos}
    };
    let componentDidMount {updater} => {
      let f1 () {state} => Some {...state, nowShowing: AllTodos};
      let f2 () {state} => Some {...state, nowShowing: ActiveTodos};
      let f3 () {state} => Some {...state, nowShowing: CompletedTodos};
      let router =
        routerMake {"/": updater f1, "/active": updater f2, "/completed": updater f3};
      router##init "/";
      None
    };
    let handleChange event {state} => Some {...state, newTodo: event##target##value};
    let handleNewTodoKeyDown event {props, state} =>
      if (event##keyCode === enterKey) {
        event##preventDefault ();
        switch (String.trim state.newTodo) {
        | "" => None
        | nonEmptyValue =>
          let todos =
            state.todos @ [
              {id: string_of_int (ReasonJs.Date.now ()), title: nonEmptyValue, completed: false}
            ];
          saveLocally todos;
          Some {...state, newTodo: "", todos}
        }
      } else {
        None
      };
    let toggleAll event {state} => {
      let checked = event##target##checked;
      let todos =
        List.map (fun todo => {...todo, TodoItem.completed: Js.to_bool checked}) state.todos;
      saveLocally todos;
      Some {...state, todos}
    };
    let toggle todoToToggle event {state} => {
      let todos =
        List.map
          (
            fun todo =>
              todo == todoToToggle ?
                {...todo, TodoItem.completed: not TodoItem.(todo.completed)} : todo
          )
          state.todos;
      saveLocally todos;
      Some {...state, todos}
    };
    let destroy todo event {state} => {
      let todos = List.filter (fun candidate => candidate !== todo) state.todos;
      saveLocally todos;
      Some {...state, todos}
    };
    let edit todo event {state} => Some {...state, editing: Some TodoItem.(todo.id)};
    let save todoToSave text {state} => {
      let todos =
        List.map
          (fun todo => todo == todoToSave ? {...todo, TodoItem.title: text} : todo) state.todos;
      Some {...state, editing: None, todos}
    };
    let cancel event {state} => Some {...state, editing: None};
    let clearCompleted event {state} => {
      let todos = List.filter (fun todo => not TodoItem.(todo.completed)) state.todos;
      saveLocally todos;
      Some {...state, todos}
    };
    let render {state, updater} => {
      let {todos, editing} = state;
      let todoItems =
        todos |>
        List.filter (
          fun todo =>
            TodoItem.(
              switch state.nowShowing {
              | ActiveTodos => not todo.completed
              | CompletedTodos => todo.completed
              | AllTodos => true
              }
            )
        ) |>
        List.map (
          fun todo => {
            let editing =
              switch editing {
              | None => false
              | Some editing => editing === TodoItem.(todo.id)
              };
            <TodoItem
              key=todo.id
              todo
              onToggle=(updater (toggle todo))
              onDestroy=(updater (destroy todo))
              onEdit=(updater (edit todo))
              editing
              onSave=(updater (save todo))
              onCancel=(updater cancel)
            />
          }
        );
      let todosLength = List.length todos;
      let completedCount =
        todos |> List.filter (fun todo => TodoItem.(todo.completed)) |> List.length;
      let activeTodoCount = todosLength - completedCount;
      let footer =
        switch (activeTodoCount, completedCount) {
        | (0, 0) => ReactRe.nullElement
        | _ =>
          <TodoFooter
            count=activeTodoCount
            completedCount
            nowShowing=state.nowShowing
            onClearCompleted=(updater clearCompleted)
          />
        };
      let main =
        todosLength === 0 ?
          ReactRe.nullElement :
          <section className="main">
            <input
              className="toggle-all"
              type_="checkbox"
              onChange=(updater toggleAll)
              checked=(activeTodoCount === 0)
            />
            <ul className="todo-list"> (ReactRe.toElement (Array.of_list todoItems)) </ul>
          </section>;
      <div>
        <header className="header">
          <h1> (ReactRe.toElement "todos") </h1>
          <input
            className="new-todo"
            placeholder="What needs to be done?"
            value=state.newTodo
            onKeyDown=(updater handleNewTodoKeyDown)
            onChange=(updater handleChange)
            autoFocus=true
          />
        </header>
        main
        footer
      </div>
    };
  };
  include ReactRe.CreateComponent TodoApp;
  let createElement = wrapProps ();
};

ReactDOMRe.render <Top /> (ReasonJs.Document.getElementsByClassName "todoapp").(0);
