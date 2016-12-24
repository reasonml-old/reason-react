external to_json_string : 'a => string = "js_json_stringify";

external parse : string => 'a = "JSON.parse" [@@bs.val];

let uuid () => {
	string_of_int (ReasonJs.Date.now ())
/*
let random = ref 0;
   let uuid = ref "";

   for i in 0 to 31 {
   	random = Math.random() * 16 | 0;
   	if (i === 8 || i === 12 || i === 16 || i === 20) {
   		uuid += '-';
   	}
   	uuid += (i === 12 ? 4 : (i === 16 ? (random & 3 | 8) : random))
   		.toString(16);
   };

   return uuid  */

 };
let pluralize count word => count === 1 ? word : word ^ "s";

let store (namespace, data) => {
  if data {
    ReasonJs.LocalStorage.setItem namespace (to_json_string data)
  };
  /* let store = ReasonJs.LocalStorage.getItem namespace; */
  /* store && parse store || [] */
	()
};
