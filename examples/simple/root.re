open ReasonJs;

Js.log "Do you see this message? If you do, then things should work!";

switch (document |> Document.getElementById "index") {
| Some root => ReactDOMRe.render <Page message="Hello!" /> root;
| None => raise Not_found;
};
