external render : ReactRe.reactElement => ReasonJs.Document.element => unit = "render" [@@bs.val] [@@bs.module
                                                                    "react-dom"
                                                                    ];

external unmountComponentAtNode : ReasonJs.Document.element => unit = "unmountComponentAtNode" [@@bs.val] [@@bs.module
                                                                    "react-dom"
                                                                    ];

external findDOMNode : 'reactRef => ReasonJs.Document.element = "findDOMNode" [@@bs.val] [@@bs.module
                                                                    "react-dom"
                                                                    ];

external domElementToObj : ReasonJs.Document.element => Js.t {..} = "%identity";
