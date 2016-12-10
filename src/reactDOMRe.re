external render : ReactRe.reactElement => DomRe.element => unit = "render" [@@bs.val] [@@bs.module
                                                                    "reactDOM"
                                                                    ];

external unmountComponentAtNode : DomRe.element => unit = "unmountComponentAtNode" [@@bs.val] [@@bs.module
                                                                    "reactDOM"
                                                                    ];

external findDOMNode : 'reactRef => DomRe.element = "findDOMNode" [@@bs.val] [@@bs.module
                                                                    "reactDOM"
                                                                    ];
